﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Input/HeartSceneInputLinker.h"
#include "Input/HeartInputActivation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(HeartSceneInputLinker)

bool UHeartSceneInputLinker::InputKey(const FInputKeyParams& Params, UObject* Target)
{
	if (TOptional<FReply> Reply = TryCallbacks(Heart::Input::FInputTrip(Params), Target, FHeartInputActivation(Params));
		Reply.IsSet())
	{
		return Reply.GetValue().IsEventHandled();
	}

	return false;
}