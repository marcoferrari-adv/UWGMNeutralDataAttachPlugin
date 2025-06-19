#include "pch.hpp"

#include "UWGMNeutralDataAttachPluginSaveListener.hpp"

#include "utilities/UWGMUtils.hpp"
#include "utilities/FileSystemUtils.hpp"
#include "configuration/UWGMClientIni.hpp"

#include <Windows.h>


void UWGMNeutralDataAttachPluginSaveListener::onPostSaveToWorkspace(wwgmtkWorkspace_ptr workspace, wwgmtkSavedModelSeq_ptr savedModels)
{

    LOG_DEBUG_INFO_MSG(m_Customizer, "Post save event wwgmtkAPIDemosWSSaveListener::onPostSaveToWorkspace");
   
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
            LOG_DEBUG_WARN_MSG(m_Customizer, "File doesn't match pattern *.sdldrw, skipping");
            continue;
        }

        savedModelName.Substitute("slddrw", "zip");

        m_Customizer->showMessage("Processing save of model " + savedModelName, wwgmtkMessageType_Info);

        LOG_DEBUG_INFO_MSG(m_Customizer,  "Expected zip file name is %s", (const char*) savedModelName);

        for (const auto neutralDataPath : m_NeutralDataPaths)
        {

            xstring sourcePath = neutralDataPath.c_str();
            sourcePath += L"\\" + savedModelName;

            m_Customizer->showMessage("Looking for neutral data zip file in path " + sourcePath, wwgmtkMessageType_Info);

            DWORD dwAttrib = GetFileAttributes(sourcePath);
            if (dwAttrib == INVALID_FILE_ATTRIBUTES || (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
                continue;

            LOG_DEBUG_INFO_MSG(m_Customizer, "Adding content %s with name %s", (const char*) sourcePath, (const char*) savedModelName);

            wwgmtkEditEpmDocument_ptr epmEdit = UWGMUtils::getEditEPMDocumentInWorkSpace(workspaceView, editor, originalModelName);
            if (epmEdit.isnull())
            {
                m_Customizer->showMessage("Unable to get editor for model " + originalModelName, wwgmtkMessageType_Error);
                continue;
            }

            wwgmtkEditContentObject_ptr editContent = epmEdit->addContent(savedModelName, "DRAWING", xfalse, sourcePath);
            if (editContent.isnull())
            {
                m_Customizer->showMessage("Unable to create cache content", wwgmtkMessageType_Error);
                continue;
            }

            LOG_DEBUG_INFO_MSG(m_Customizer, "Opening content for write");

            wwgmtkCachedFile_ptr cachedFile = editor->openContentForWrite(editContent);
            if (cachedFile.isnull())
            {
                m_Customizer->showMessage("Unable to open content for write", wwgmtkMessageType_Error);
                continue;
            }

            xstring destinationPath = cachedFile->getHandle();

            LOG_DEBUG_INFO_MSG(m_Customizer, "Opening writing content to %s", (const char*) destinationPath);

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




