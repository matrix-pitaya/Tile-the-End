#pragma once

#include"def/def_delete_copy_move.h"

#include"Iphysics.h"

#include"thread/threadapi.h"

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
		class PhysicsCmdParser
		{
			DELETE_COPY_AND_MOVE(PhysicsCmdParser)

		private:
			struct PhysicsCmd
			{

			};

		public:
			PhysicsCmdParser() = default;
			~PhysicsCmdParser() = default;

			inline void ParseCmd()
			{
				while (!queue.empty())
				{
					const PhysicsCmd& cmd = queue.front();
					queue.pop();
				}
			}
			inline bool IsRemainCmd()
			{
				return !queue.empty();
			}

		private:
			std::queue<PhysicsCmd> queue;
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

#pragma region PhysicsThreadFunction
	private:
		bool InitPhysicsThread();
		void PhysicsThread();
		void Simulate();
		void SwapBufferIfReady();
		void RebuildWorldFromBuffer();
		void WriteBackResultsToBuffer();
		void ProcessPhysicsCmd();
#pragma endregion

	private:
		void InterpolateAndWriteBack();

	private:
		std::condition_variable cond;
		std::atomic<bool> isRunning = false;
		std::atomic<unsigned int> times = 0;
		std::mutex mutex;
		Core::Thread::ThreadToken physicsThreadToken;
		PhysicsCmdParser physicsCmdParser;


		//双缓冲
		std::vector<PhysicsData> bufferA;
		std::vector<PhysicsData> bufferB;
		std::atomic<bool> isBufferAReady = false;
		std::atomic<bool> isBufferBReady = false;

		bool isInitialized = false;
		bool isReleased = false;
	};
}