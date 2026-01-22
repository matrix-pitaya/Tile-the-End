#include"pitaya/physics.h"
#include"log/logapi.h"

bool Physics::PitayaPhysics::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	physicsThread = std::thread(&PitayaPhysics::PhysicsThread, this);

	isInitialized = true;
	return true;
}
void Physics::PitayaPhysics::Release()
{
	if (isReleased)
	{
		return;
	}

	isRunning = false;
	cond.notify_one();
	if (physicsThread.joinable())
	{
		physicsThread.join();
	}

	isReleased = true;
}
void Physics::PitayaPhysics::OnFixupdata(unsigned int times)
{
	if (!isRunning)
	{
		return;
	}

	this->times = times;
	//唤醒物理线程
	cond.notify_one();
	//判断能否交换缓冲区
	SwapBufferIfReady();
	//插值写回执行结果
	InterpolateAndWriteBack();
}
bool Physics::PitayaPhysics::InitPhysicsThread()
{
	isRunning = true;
	return true;
}
void Physics::PitayaPhysics::PhysicsThread()
{
	if (!InitPhysicsThread())
	{
		Core::Log::Log(Core::Log::LogLevel::Error, "Init Physics Thread Fail!");
		throw std::runtime_error("Init Physics Thread Fail!");
		return;
	}

	while (true)
	{
		std::unique_lock<std::mutex> lock(mutex);
		cond.wait(lock, [this] { return physicsCmdParser.IsRemainCmd() || times > 0 || !isRunning; });

		//执行主线程写入的物理命令 调整物理世界组件数量
		ProcessPhysicsCmd();

		//读取主线程写入的buffer重构物理世界
		RebuildWorldFromBuffer();

		while (times-- > 0)
		{
			//模拟物理世界
			Simulate();
		}

		//写回buffer
		RebuildWorldFromBuffer();

		if (!physicsCmdParser.IsRemainCmd() && times <= 0 && !isRunning)
		{
			break;
		}
	}
}
void Physics::PitayaPhysics::Simulate()
{
	//TODO: 刚体响应速度 → 碰撞箱执行 → 触发回调函数 → 位置修正
}
void Physics::PitayaPhysics::SwapBufferIfReady()
{

}
void Physics::PitayaPhysics::RebuildWorldFromBuffer()
{

}
void Physics::PitayaPhysics::WriteBackResultsToBuffer()
{

}
void Physics::PitayaPhysics::ProcessPhysicsCmd()
{
	physicsCmdParser.ParseCmd();
}
void Physics::PitayaPhysics::InterpolateAndWriteBack()
{

}