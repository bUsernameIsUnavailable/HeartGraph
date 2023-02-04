﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "UI/HeartWidgetInputLinker.h"
#include "Components/Widget.h"
#include "UI/HeartInputActivation.h"
#include "UI/HeartUMGContextObject.h"

using namespace Heart::Input;

FReply UHeartWidgetInputLinker::HandleOnMouseWheel(UWidget* Widget, const FGeometry& InGeometry, const FPointerEvent& PointerEvent)
{
	FHeartWidgetInputTrip MouseWheelAxisTrip;
	MouseWheelAxisTrip.Key = EKeys::MouseWheelAxis;
	MouseWheelAxisTrip.Type = Press; // Mouse wheel events must always use the 'Press' type

	TArray<FConditionalInputCallback> Callbacks;
	InputCallbackMappings.MultiFind(MouseWheelAxisTrip, Callbacks);
	Callbacks.Sort();
	for (auto&& ConditionalInputCallback : Callbacks)
	{
		bool PassedCondition = true;

		if (ConditionalInputCallback.Condition.IsBound())
		{
			PassedCondition = ConditionalInputCallback.Condition.Execute(Widget);
		}

		if (PassedCondition && ConditionalInputCallback.Callback.IsBound())
		{
			FHeartInputActivation Activation;
			Activation.ActivationValue = PointerEvent.GetWheelDelta();
			FReply Reply = ConditionalInputCallback.Callback.Execute(Widget, Activation);

			if (ConditionalInputCallback.Layer == Event)
			{
				if (Reply.IsEventHandled())
				{
					return Reply;
				}
			}
		}
	}

	return FReply::Unhandled();
}

FReply UHeartWidgetInputLinker::HandleOnMouseButtonDown(UWidget* Widget, const FGeometry& InGeometry, const FPointerEvent& PointerEvent)
{
	FHeartWidgetInputTrip Trip;
	Trip.Key = PointerEvent.GetEffectingButton().IsValid() ? PointerEvent.GetEffectingButton() : *PointerEvent.GetPressedButtons().CreateConstIterator();
	Trip.Type = Press;

	TArray<FConditionalInputCallback> Callbacks;
	InputCallbackMappings.MultiFind(Trip, Callbacks);
	Callbacks.Sort();
	for (auto&& ConditionalInputCallback : Callbacks)
	{
		bool PassedCondition = true;

		if (ConditionalInputCallback.Condition.IsBound())
		{
			PassedCondition = ConditionalInputCallback.Condition.Execute(Widget);
		}

		if (PassedCondition && ConditionalInputCallback.Callback.IsBound())
		{
			FHeartInputActivation Activation;
			Activation.ActivationValue = 1;
			FReply Reply = ConditionalInputCallback.Callback.Execute(Widget, Activation);

			if (ConditionalInputCallback.Layer == Event)
			{
				if (Reply.IsEventHandled())
				{
					return Reply;
				}
			}
		}
	}

	TArray<FConditionalDragDropTrigger> DropDropTriggerArray;
	DragDropTriggers.MultiFind(Trip, DropDropTriggerArray);
	DropDropTriggerArray.Sort();
	for (auto&& ConditionalDropDropTrigger : DropDropTriggerArray)
	{
		bool PassedCondition = true;

		if (ConditionalDropDropTrigger.Condition.IsBound())
		{
			PassedCondition = ConditionalDropDropTrigger.Condition.Execute(Widget);
		}

		if (PassedCondition && ConditionalDropDropTrigger.Callback.IsBound())
		{
			const TSharedPtr<SWidget> SlateWidgetDetectingDrag = Widget->GetCachedWidget();
			if (SlateWidgetDetectingDrag.IsValid())
			{
				FReply Reply = FReply::Handled().DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), PointerEvent.GetEffectingButton());

				if (ConditionalDropDropTrigger.Layer == Event)
				{
					if (Reply.IsEventHandled())
					{
						return Reply;
					}
				}
			}
		}
	}

	return FReply::Unhandled();
}

FReply UHeartWidgetInputLinker::HandleOnMouseButtonUp(UWidget* Widget, const FGeometry& InGeometry, const FPointerEvent& PointerEvent)
{
	FHeartWidgetInputTrip Trip;
	Trip.Key = PointerEvent.GetEffectingButton().IsValid() ? PointerEvent.GetEffectingButton() : *PointerEvent.GetPressedButtons().CreateConstIterator();
	Trip.Type = Release;

	TArray<FConditionalInputCallback> Callbacks;
	InputCallbackMappings.MultiFind(Trip, Callbacks);
	Callbacks.Sort();
	for (auto&& ConditionalInputCallback : Callbacks)
	{
		bool PassedCondition = true;

		if (ConditionalInputCallback.Condition.IsBound())
		{
			PassedCondition = ConditionalInputCallback.Condition.Execute(Widget);
		}

		if (PassedCondition && ConditionalInputCallback.Callback.IsBound())
		{
			FHeartInputActivation Activation;
			Activation.ActivationValue = 0;
			FReply Reply = ConditionalInputCallback.Callback.Execute(Widget, Activation);

			if (ConditionalInputCallback.Layer == Event)
			{
				if (Reply.IsEventHandled())
				{
					return Reply;
				}
			}
		}
	}

	return FReply::Unhandled();
}

FReply UHeartWidgetInputLinker::HandleOnKeyDown(UWidget* Widget, const FGeometry& InGeometry, const FKeyEvent& KeyEvent)
{
	FHeartWidgetInputTrip Trip;
	Trip.Key = KeyEvent.GetKey();
	Trip.Type = Press;

	TArray<FConditionalInputCallback> Callbacks;
	InputCallbackMappings.MultiFind(Trip, Callbacks);
	Callbacks.Sort();
	for (auto&& ConditionalInputCallback : Callbacks)
	{
		bool PassedCondition = true;

		if (ConditionalInputCallback.Condition.IsBound())
		{
			PassedCondition = ConditionalInputCallback.Condition.Execute(Widget);
		}

		if (PassedCondition && ConditionalInputCallback.Callback.IsBound())
		{
			FHeartInputActivation Activation;
			Activation.ActivationValue = 1;
			FReply Reply = ConditionalInputCallback.Callback.Execute(Widget, Activation);

			if (ConditionalInputCallback.Layer == Event)
			{
				if (Reply.IsEventHandled())
				{
					return Reply;
				}
			}
		}
	}

	return FReply::Unhandled();
}

FReply UHeartWidgetInputLinker::HandleOnKeyUp(UWidget* Widget, const FGeometry& InGeometry, const FKeyEvent& KeyEvent)
{
	FHeartWidgetInputTrip Trip;
	Trip.Key = KeyEvent.GetKey();
	Trip.Type = Release;

	TArray<FConditionalInputCallback> Callbacks;
	InputCallbackMappings.MultiFind(Trip, Callbacks);
	Callbacks.Sort();
	for (auto&& ConditionalInputCallback : Callbacks)
	{
		bool PassedCondition = true;

		if (ConditionalInputCallback.Condition.IsBound())
		{
			PassedCondition = ConditionalInputCallback.Condition.Execute(Widget);
		}

		if (PassedCondition && ConditionalInputCallback.Callback.IsBound())
		{
			FHeartInputActivation Activation;
			Activation.ActivationValue = 0;
			FReply Reply = ConditionalInputCallback.Callback.Execute(Widget, Activation);

			if (ConditionalInputCallback.Layer == Event)
			{
				if (Reply.IsEventHandled())
				{
					return Reply;
				}
			}
		}
	}

	return FReply::Unhandled();
}

UHeartDragDropOperation* UHeartWidgetInputLinker::HandleOnDragDetected(UWidget* Widget, const FGeometry& InGeometry, const FPointerEvent& PointerEvent)
{
	FHeartWidgetInputTrip Trip;
	Trip.Type = Press;
	Trip.Key = PointerEvent.GetEffectingButton().IsValid() ? PointerEvent.GetEffectingButton() : *PointerEvent.GetPressedButtons().CreateConstIterator();

	TArray<FConditionalDragDropTrigger> DropDropTriggerArray;
	DragDropTriggers.MultiFind(Trip, DropDropTriggerArray);
	DropDropTriggerArray.Sort();
	for (auto&& DragDropTrigger : DropDropTriggerArray)
	{
		if (DragDropTrigger.Callback.IsBound())
		{
			UHeartDragDropOperation* DragDropOperation = DragDropTrigger.Callback.Execute(Widget);
			DragDropOperation->SummonedBy = Widget;

			if (Widget->Implements<UHeartUMGContextObject>())
			{
				DragDropOperation->Payload = IHeartUMGContextObject::Execute_GetContextObject(Widget);
			}

			// @todo its a little bogus to create the ddo then call this every time to see if it will be handled :/
			if (DragDropOperation->SetupDragDropOperation())
			{
				return DragDropOperation;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Created DDO (%s) unnecessarily, figure out why"), *DragDropOperation->GetClass()->GetName())
			}
		}
	}

	return nullptr;
}

bool UHeartWidgetInputLinker::HandleNativeOnDragOver(UWidget* Widget, const FGeometry& InGeometry, const FDragDropEvent& DragDropEvent, UDragDropOperation* InOperation)
{
	if (auto&& HeartDDO = Cast<UHeartDragDropOperation>(InOperation))
	{
		return HeartDDO->OnHoverWidget(Widget);
	}

	return false;
}

bool UHeartWidgetInputLinker::HandleNativeOnDrop(UWidget* Widget, const FGeometry& InGeometry, const FDragDropEvent& DragDropEvent,
												 UDragDropOperation* InOperation)
{
	if (auto&& HeartDDO = Cast<UHeartDragDropOperation>(InOperation))
	{
		return HeartDDO->CanDropOnWidget(Widget);
	}

	return false;
}

void UHeartWidgetInputLinker::HandleNativeOnDragEnter(UWidget* Widget, const FGeometry& InGeometry, const FDragDropEvent& DragDropEvent,
	UDragDropOperation* InOperation)
{
	// Nothing here yet
}

void UHeartWidgetInputLinker::HandleNativeOnDragLeave(UWidget* Widget, const FDragDropEvent& DragDropEvent,
	UDragDropOperation* InOperation)
{
	// Nothing here yet
}

void UHeartWidgetInputLinker::HandleNativeOnDragCancelled(UWidget* Widget, const FDragDropEvent& DragDropEvent,
	UDragDropOperation* InOperation)
{
	// Nothing here yet
}

FReply UHeartWidgetInputLinker::HandleManualInput(UWidget* Widget, /*const FGeometry& InGeometry,*/ FName Key, FHeartInputActivation Activation)
{
	FHeartWidgetInputTrip Trip;
	Trip.Type = Manual;
	Trip.CustomKey = Key;

	TArray<FConditionalInputCallback> Callbacks;
	InputCallbackMappings.MultiFind(Trip, Callbacks);
	Callbacks.Sort();
	for (auto&& ConditionalInputCallback : Callbacks)
	{
		bool PassedCondition = true;

		if (ConditionalInputCallback.Condition.IsBound())
		{
			PassedCondition = ConditionalInputCallback.Condition.Execute(Widget);
		}

		if (PassedCondition && ConditionalInputCallback.Callback.IsBound())
		{
			FReply Reply = ConditionalInputCallback.Callback.Execute(Widget, Activation);

			if (ConditionalInputCallback.Layer == Event)
			{
				if (Reply.IsEventHandled())
				{
					return Reply;
				}
			}
		}
	}

	return FReply::Unhandled();
}

TArray<FHeartManualInputQueryResult> UHeartWidgetInputLinker::QueryManualTriggers(const UWidget* Widget) const
{
	TArray<FHeartManualInputQueryResult> Results;

	for (auto&& ConditionalInputCallback : InputCallbackMappings)
	{
		if (ConditionalInputCallback.Key.Type != Manual)
		{
			continue;
		}

		bool PassedCondition = true;

		if (ConditionalInputCallback.Value.Condition.IsBound())
		{
			PassedCondition = ConditionalInputCallback.Value.Condition.Execute(Widget);
		}

		if (PassedCondition)
		{
			if (ConditionalInputCallback.Value.Description.IsBound())
			{
				Results.Add({ConditionalInputCallback.Key.CustomKey, ConditionalInputCallback.Value.Description.Execute(Widget)});
			}
			else
			{
				Results.Add({ConditionalInputCallback.Key.CustomKey});
			}
		}
	}

	return Results;
}

void UHeartWidgetInputLinker::BindInputCallback(const FHeartWidgetInputTrip& Trip, const FConditionalInputCallback& InputCallback)
{
	InputCallbackMappings.Add(Trip, InputCallback);
}

void UHeartWidgetInputLinker::UnbindInputCallback(const FHeartWidgetInputTrip& Trip)
{
	InputCallbackMappings.Remove(Trip);
}

void UHeartWidgetInputLinker::BindToOnDragDetected(const FHeartWidgetInputTrip& Trip, const FConditionalDragDropTrigger& DragDropTrigger)
{
	DragDropTriggers.Add(Trip, DragDropTrigger);
}

void UHeartWidgetInputLinker::UnbindToOnDragDetected(const FHeartWidgetInputTrip& Trip)
{
	DragDropTriggers.Remove(Trip);
}