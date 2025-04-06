// Wyy All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorTypes/WarriorEnumTypes.h"


class FWarriorCountDownAction : public FPendingLatentAction
{
public:
	FWarriorCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, EWarriorCountDownActionOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false), TotalCountDownTime(InTotalCountDownTime), UpdateInterval(InUpdateInterval), OutRemainingTime(InOutRemainingTime),
			CountDownOutput(InCountDownOutput), ExecutionFunction(LatentInfo.ExecutionFunction), OutputLink(LatentInfo.Linkage),
				CallbackTarget(LatentInfo.CallbackTarget), ElapsedInterval(0.f), ElapsedTimeSinceStart(0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("CountDown Action Created!"));
	}

	// 每次tick都会调用该函数，重写该函数以实现自己的功能
	virtual void UpdateOperation(FLatentResponse& Response) override;

	void CancelAction();

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EWarriorCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};

/**
class WARRIOR_API WarriorCountDownAction
{
public:
	WarriorCountDownAction();
	~WarriorCountDownAction();
};
*/
