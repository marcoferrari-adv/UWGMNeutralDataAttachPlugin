#include "pch.hpp"

#include "UWGMNeutralDataAttachPluginSaveListener.hpp"

#include "utilities/UWGMUtils.hpp"
#include "utilities/FileSystemUtils.hpp"
#include "configuration/UWGMClientIni.hpp"

#include <Windows.h>


void UWGMNeutralDataAttachPluginSaveListener::onPostSaveToWorkspace(wwgmtkWorkspace_ptr workspace, wwgmtkSavedModelSeq_ptr savedModels)
{
#if DEBUG
    m_Customizer->showMessage("Post save event wwgmtkAPIDemosWSSaveListener::onPostSaveToWorkspace", wwgmtkMessageType_Info);
#endif
   
    wwgmtkWorkspaceViewer_ptr workspaceView = UWGMUtils::getWorkspaceViewer(m_Customizer->getClient(), workspace);
    if (workspaceView.isnull())
    {
        m_Customizer->showMessage("Failed to retrieve workspace view", wwgmtkMessageType_Error);
        return;
    }

    wwgmtkWorkspaceEditor_ptr editor = workspaceView->getEditor();
    if (editor.isnull())
    {
        m_Customizer->showMessage("Failed to retrieve workspace editor", wwgmtkMessageType_Error);
        return;
    }

    bool isAnythingChanged = false;
    xint numberOfModels = savedModels.isnull() ? 0 : savedModels->getarraysize();
    for (xint i = 0; i < numberOfModels; i++)
    {
        xstring originalModelName = savedModels->get(i)->getName();
        xstring savedModelName = originalModelName.ToLower();
        m_Customizer->showMessage("Processing save of model " + savedModelName, wwgmtkMessageType_Info);
        if (savedModelName.Match("*.sdldrw"))
        {
#if DEBUG
            m_Customizer->showMessage("File doesn't match pattern *.sdldrw, skipping", wwgmtkMessageType_Warning);
#endif
            continue;
        }

        savedModelName.Substitute("slddrw", "zip");

#if DEBUG
        m_Customizer->showMessage("Expected zip file name is " + savedModelName, wwgmtkMessageType_Info);
#endif

        for (const auto neutralDataPath : m_NeutralDataPaths)
        {

            xstring sourcePath = neutralDataPath.c_str();
            sourcePath += L"\\" + savedModelName;

            m_Customizer->showMessage("Looking for neutral data zip file in path " + sourcePath, wwgmtkMessageType_Info);

            DWORD dwAttrib = GetFileAttributes(sourcePath);
            if (dwAttrib == INVALID_FILE_ATTRIBUTES || (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
                continue;

#if DEBUG
            m_Customizer->showMessage("Adding content " + sourcePath + " with name " + savedModelName, wwgmtkMessageType_Info);
#endif
            wwgmtkEditEpmDocument_ptr epmEdit = UWGMUtils::getEditEPMDocumentInWorkSpace(workspaceView, editor, originalModelName);
            if (epmEdit.isnull())
            {
                m_Customizer->showMessage("Unable to get editor for model " + originalModelName, wwgmtkMessageType_Error);
                continue;
            }

            wwgmtkEditContentObject_ptr editContent = epmEdit->addContent(savedModelName, "GENERAL", xfalse, sourcePath);
            if (editContent.isnull())
            {
                m_Customizer->showMessage("Unable to create cache content", wwgmtkMessageType_Error);
                continue;
            }

#if DEBUG
            m_Customizer->showMessage("Opening content for write", wwgmtkMessageType_Info);
#endif

            wwgmtkCachedFile_ptr cachedFile = editor->openContentForWrite(editContent);
            if (cachedFile.isnull())
            {
                m_Customizer->showMessage("Unable to open content for write", wwgmtkMessageType_Error);
                continue;
            }

            xstring destinationPath = cachedFile->getHandle();
#if DEBUG
            m_Customizer->showMessage("Opening writing content to " + destinationPath, wwgmtkMessageType_Info);
#endif

            if (!FileSystemUtils::copyFile(sourcePath, destinationPath))
            {
                cachedFile->close();
                m_Customizer->showMessage("Unable to copy file from " + sourcePath + " to " + destinationPath, wwgmtkMessageType_Error);
                continue;
            }
            cachedFile->close();
            editor->commit();

            m_Customizer->showMessage("Deleting file " + sourcePath, wwgmtkMessageType_Info);
            DeleteFile(sourcePath);
            isAnythingChanged = true;
        }
    }
    
    
    if (isAnythingChanged)
    {
        editor->release();
    }
    else
    {
        editor->abort();
        editor->release();
    }
        
    editor = nullptr;
}




