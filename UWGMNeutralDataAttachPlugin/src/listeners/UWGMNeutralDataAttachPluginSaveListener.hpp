#pragma once
#include <wwgmtk.h>

#include "customizer/UWGMNeutralDataAttachPluginCustomizer.hpp"

class UWGMNeutralDataAttachPluginSaveListener : public virtual wwgmtkWorkspaceSaveListener
{
public:
    UWGMNeutralDataAttachPluginSaveListener(UWGMNeutralDataAttachPluginCustomizer_ptr customizer, vector<std::wstring>& neutralDataPaths) :
        m_Customizer(customizer), m_NeutralDataPaths(neutralDataPaths)
    {
    }

    virtual wwgmtkSaveConflictSeq_ptr onPreSaveToWorkspace(wwgmtkWorkspace_ptr workspace, wwgmtkSavedModelSeq_ptr savedModels)
    {
        return xobjectnil;
    }

    virtual void onPostSaveToWorkspace(wwgmtkWorkspace_ptr workspace, wwgmtkSavedModelSeq_ptr savedModels);

    virtual void showWorkspaceAndModels(wwgmtkWorkspace_ptr workspace, wwgmtkSavedModelSeq_ptr savedModels)
    {
    }

protected:
    UWGMNeutralDataAttachPluginCustomizer_ptr m_Customizer;
    vector<std::wstring> m_NeutralDataPaths;
};