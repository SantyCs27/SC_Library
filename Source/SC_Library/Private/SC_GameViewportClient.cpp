// Copyright Santiago Cañas. All Rights Reserved.


#include "SC_GameViewportClient.h"

/**
 * User is by default allowed to quit game without being stopped.
 * Just execute the SetAllowWindowClose node on Event Init in your Game Instance for example and set it to true.
 * If he tries to quit before that... don't judge him.
 */
bool USC_GameViewportClient::bAllowWindowClosing = true;

/**
 * Here we add our own handling of the Request.
 * If the user is allowed, it will return true (which means he is allowed to leave the game without being stopped.
 * But if he is not allowed to quit, we block this with return false and Execute our Delegate.
 */
bool USC_GameViewportClient::WindowCloseRequested()
{
	if (bAllowWindowClosing)
	{
		return true;
	}
	UserWindowCloseRequested.Execute();
	return false;
}

/**
 * Allow / Disallow the user to close the window without being stopped.
 */
void USC_GameViewportClient::SetAllowWindowClose(bool bAllowWindowClose)
{
	bAllowWindowClosing = bAllowWindowClose;
}

/**
 * Can be used to check if the user is currently allowed to close the window without being stopped.
 */
bool USC_GameViewportClient::GetAllowWindowClose()
{
	return bAllowWindowClosing;
}

/**
 * Bind this Event for example in your UI, so when the user requests the close you can open up a
 * "Do you really want to quit?" window we all love.
 */
void USC_GameViewportClient::BindOnUserWindowCloseRequested(FOnUserWindowCloseRequested OnUserWindowCloseRequested)
{
	UserWindowCloseRequested = OnUserWindowCloseRequested;
}