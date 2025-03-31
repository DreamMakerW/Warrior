// Wyy All Rights Reserved


#include "WarriorTypes/WarriorCountDownAction.h"

void FWarriorCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		// 当外部设置bNeedToCancel = true时，中止倒计时
		CountDownOutput = EWarriorCountDownActionOutput::Cancelled;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		// 当累计时间超过总倒计时时间
		CountDownOutput = EWarriorCountDownActionOutput::Completed;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	if (ElapsedInterval < UpdateInterval)
	{
		// 自上次更新后的时间未达到UpdateInterval时直接累加帧时间
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		// 更新累计时间，如果UpdateInterval > 0，按固定间隔累加；否则直接使用帧时间
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();
		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;
		CountDownOutput = EWarriorCountDownActionOutput::Updated;
		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);
		// 重置间隔计时
		ElapsedInterval = 0.f;
	}
}

void FWarriorCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}
