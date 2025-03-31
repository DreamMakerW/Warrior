// Wyy All Rights Reserved


#include "WarriorTypes/WarriorCountDownAction.h"

void FWarriorCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		// ���ⲿ����bNeedToCancel = trueʱ����ֹ����ʱ
		CountDownOutput = EWarriorCountDownActionOutput::Cancelled;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		// ���ۼ�ʱ�䳬���ܵ���ʱʱ��
		CountDownOutput = EWarriorCountDownActionOutput::Completed;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	if (ElapsedInterval < UpdateInterval)
	{
		// ���ϴθ��º��ʱ��δ�ﵽUpdateIntervalʱֱ���ۼ�֡ʱ��
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		// �����ۼ�ʱ�䣬���UpdateInterval > 0�����̶�����ۼӣ�����ֱ��ʹ��֡ʱ��
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();
		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;
		CountDownOutput = EWarriorCountDownActionOutput::Updated;
		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);
		// ���ü����ʱ
		ElapsedInterval = 0.f;
	}
}

void FWarriorCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}
