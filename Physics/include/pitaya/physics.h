#pragma once

#include"def/def_delete_copy_move.h"

#include"Iphysics.h"

#include<thread>
#include<atomic>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<vector>

namespace Physics
{
	class PitayaPhysics : public Interface::Physics
	{
		DELETE_COPY_AND_MOVE(PitayaPhysics)

	private:
		struct PhysicsCmd
		{

		};
		struct PhysicsData
		{

		};

	public:
		PitayaPhysics() = default;
		~PitayaPhysics() { Release(); }

		bool Initialize() override;
		void Release() override;

		//唤醒物理线程
		void OnFixupdata(unsigned int times) override;

	private:
#pragma region PhysicsThreadFunction
		bool InitPhysicsThread();
		void PhysicsThread();
		void Simulate();
		void SwapBufferIfReady();
		void RebuildWorldFromBuffer();
		void WriteBackResultsToBuffer();
		void ProcessPhysicsCmd();
#pragma endregion

		void InterpolateAndWriteBack();

	private:
		std::thread physicsThread;
		std::condition_variable cond;
		std::atomic<bool> isRunning = false;
		std::atomic<unsigned int> times = 0;
		std::mutex mutex;
		std::queue<PhysicsCmd> queue;

		//双缓冲
		std::vector<PhysicsData> bufferA;
		std::vector<PhysicsData> bufferB;
		std::atomic<bool> isBufferAReady = false;
		std::atomic<bool> isBufferBReady = false;

		bool isInitialized = false;
		bool isReleased = false;
	};
}