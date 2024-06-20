#ifndef STAGEMGR_HPP__
#define STAGEMGR_HPP__
#include <stack>
#include <memory>
class Stage;
class StageMgr
{

        std::stack<std::unique_ptr<Stage>> stages;
    public:
        StageMgr();
        ~StageMgr() = default;

        void pushStage(std::unique_ptr<Stage> stage);
        void popStage();
        Stage* getCurrentStage();
};
#endif