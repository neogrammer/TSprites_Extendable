#include "StageMgr.hpp"
#include "StageSandbox.hpp"

StageMgr::StageMgr()
	: stages{}
{
	pushStage(std::make_unique<StageSandbox>(*this));
}

void StageMgr::pushStage(std::unique_ptr<Stage> stage)
{
	stages.push(std::move(stage));
}

void StageMgr::popStage()
{
	stages.pop();
}

Stage* StageMgr::getCurrentStage()
{
	return stages.top().get();
}
