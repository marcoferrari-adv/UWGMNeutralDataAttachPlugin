#pragma once
#include <wwgmtkcustomizer.h>

class UWGMUtils
{
public:
	static wwgmtkWorkspaceViewer_ptr getWorkspaceViewer(wwgmtkClient_ptr client,wwgmtkWorkspace_ptr workspace);
	static wwgmtkWorkspaceViewer_ptr getWorkspaceViewer(wwgmtkClient_ptr client);
	static wwgmtkWorkspaceCache_ptr getWorkspaceCache(wwgmtkClient_ptr client);
	static wwgmtkWorkspaceObject_ptr getObjectInWorkSpace(wwgmtkWorkspaceViewer_ptr viewer, xstring epmName);
	static wwgmtkEpmDocument_ptr getEPMDocumentInWorkSpace(wwgmtkWorkspaceViewer_ptr viewer, xstring epmName);
	static wwgmtkEditEpmDocument_ptr getEditEPMDocumentInWorkSpace(wwgmtkWorkspaceViewer_ptr viewer, wwgmtkWorkspaceEditor_ptr editor, xstring epmName);
};