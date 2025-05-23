#include "pch.hpp"

#include "UWGMUtils.hpp"

wwgmtkWorkspaceViewer_ptr UWGMUtils::getWorkspaceViewer(wwgmtkClient_ptr client, wwgmtkWorkspace_ptr workspace)
{
    wwgmtkWorkspaceCache_ptr cache = workspace->getWorkspaceCache();
    if (cache.isnull())
    {
        wwgmtkClientWindow_ptr tkWin = client->getTopWindow();
        tkWin->showMessage("Unable to get client cache", wwgmtkMessageType_Error);
        return wwgmtkWorkspaceViewer_ptr(nullptr);
    }
    return cache->getViewer(xtrue);
}

wwgmtkWorkspaceViewer_ptr UWGMUtils::getWorkspaceViewer(wwgmtkClient_ptr client)
{
    wwgmtkWorkspaceCache_ptr cache = getWorkspaceCache(client);
    if (cache.isnull())
    {
        wwgmtkClientWindow_ptr tkWin = client->getTopWindow();
        tkWin->showMessage("Unable to get client cache", wwgmtkMessageType_Error);
        return wwgmtkWorkspaceViewer_ptr(nullptr);
    }
	return cache->getViewer(xtrue);
}

wwgmtkWorkspaceCache_ptr UWGMUtils::getWorkspaceCache(wwgmtkClient_ptr client)
{
    wwgmtkServerRegistry_ptr servRegistry = client->getServerRegistry();
    if (servRegistry.isnull())
        return wwgmtkWorkspaceCache_ptr(nullptr);

    wwgmtkWorkspace_ptr workspace = servRegistry->getWorkspaceByServerName(NULL);
    if (workspace.isnull())
        return wwgmtkWorkspaceCache_ptr(nullptr);

    return workspace->getWorkspaceCache();
}

wwgmtkWorkspaceObject_ptr UWGMUtils::getObjectInWorkSpace(wwgmtkWorkspaceViewer_ptr viewer, xstring epmName)
{
    wwgmtkWorkspaceObject_ptr wsObject = viewer->getWorkspaceObjectByEpmName(epmName);
    return wsObject;
}

wwgmtkEpmDocument_ptr UWGMUtils::getEPMDocumentInWorkSpace(wwgmtkWorkspaceViewer_ptr viewer, xstring epmName)
{
    wwgmtkWorkspaceObject_ptr wsObject = getObjectInWorkSpace(viewer, epmName);
    if (wsObject.isnull() || !wsObject->getIsEpmDocument())
        return wwgmtkEpmDocument_ptr(nullptr);

    return wsObject->getEpmDocument();
}

wwgmtkEditEpmDocument_ptr UWGMUtils::getEditEPMDocumentInWorkSpace(wwgmtkWorkspaceViewer_ptr viewer, wwgmtkWorkspaceEditor_ptr editor, xstring epmName)
{
    wwgmtkWorkspaceObject_ptr wsObject = getObjectInWorkSpace(viewer, epmName);
    if (wsObject.isnull())
        return wwgmtkEditEpmDocument_ptr(nullptr);

    wwgmtkEditWorkspaceObject_ptr editObj = editor->editWorkspaceObject(wsObject);
    if (editObj.isnull() || !editObj->getIsEpmDocument() || !editObj->getIsEditableInWorkspace())
        return wwgmtkEditEpmDocument_ptr(nullptr);

    return editObj->getEditEpmDocument(); 
    
}