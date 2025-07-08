#include "pch.hpp"

#include "UWGMNeutralDataAttachPluginCustomizer.hpp"
#include "listeners/UWGMNeutralDataAttachPluginSaveListener.hpp"
#include "configuration/UWGMClientIni.hpp"
#include "utilities/StopWatch.hpp"
#include "utilities/Logger.hpp"

UWGMNeutralDataAttachPluginCustomizer::UWGMNeutralDataAttachPluginCustomizer()
	: m_ClientIni(UWGMClientIni::getInstance())
{
}

xint UWGMNeutralDataAttachPluginCustomizer::initialize(wwgmtkClient_ptr client)
{
	StopWatch sw;
	sw.start();

	m_Client = client;
	showMessage("UWGMNeutralDataAttachPlugin Application initialize", wwgmtkMessageType_Info);

	showMessage(xstring::Printf("UWGM client init map is %ls", m_ClientIni->dumpIniMap().c_str()), wwgmtkMessageType_Info, xfalse);

	std::wstring neutralDataConfiguiredValue = m_ClientIni->readProperty(L"SolidWorks", L"upload.autoattach.searchpath");

	showMessage(xstring::Printf("UWGM client upload property is %ls", neutralDataConfiguiredValue.c_str()), wwgmtkMessageType_Info, xfalse);

	if (neutralDataConfiguiredValue.empty())
	{
		showMessage("upload.autoattach.searchpath not configured in wgmclient.ini, no neutral data attach will be perfomed", wwgmtkMessageType_Error);
		return wwgmtkError_NoError;
	}

	vector<std::wstring> neutralDataPaths = UWGMClientIni::getMultiValueTokens(neutralDataConfiguiredValue);
	if (neutralDataPaths.empty())
	{
		showMessage("Unable to evaluate neutral data paths", wwgmtkMessageType_Error);
		return wwgmtkError_NoError;
	}

	wwgmtkWorkspaceSaveListener_ptr wsListener = new UWGMNeutralDataAttachPluginSaveListener(this, neutralDataPaths);
	wwgmtkWorkspaceOperationsRegistry_ptr wsOpRegistry = m_Client->getWorkspaceOperationsRegistry();
	wsOpRegistry->registerSaveListener(wsListener);
	showMessage("CleanUWGMNeutralDataFolder save listener registered", wwgmtkMessageType_Info, xfalse);

	showMessage(xstring::Printf("CleanUWGMNeutralDataFolder inzialization took %f ms", sw.elapsedMilliseconds()), wwgmtkMessageType_Info, xfalse);

	return wwgmtkError_NoError;
}

xanydictionary_ptr UWGMNeutralDataAttachPluginCustomizer::executeCommand(xanydictionary_ptr params)
{
	showMessage("Recived executeCommand call", wwgmtkMessageType_Info);
	return xanydictionary::create();
}

xstring UWGMNeutralDataAttachPluginCustomizer::executeJSCommand(xrstring params)
{
	return xstringnil;
}

void UWGMNeutralDataAttachPluginCustomizer::showMessage(xstring msg, xint msgType, xbool forceUWGMClientPrint, xbool toFile)
{
	if (msg.IsNull() || msg.IsEmpty())
		return;

#ifdef DEBUG || RELEASE
	wwgmtkClientWindow_ptr tkWin = m_Client->getTopWindow();
	if (!tkWin.isnull())
		tkWin->showMessage(msg, msgType);
#else
	if (forceUWGMClientPrint)
	{
		wwgmtkClientWindow_ptr tkWin = m_Client->getTopWindow();
		if (!tkWin.isnull())
			tkWin->showMessage(msg, msgType);
	}
#endif // DEBUG || RELEASE

	if (toFile == xtrue)
	{
		switch (msgType) {
		case wwgmtkMessageType_Info:
			Logger::get().debug((const char*)msg);
			break;
		case wwgmtkMessageType_Warning:
			Logger::get().warn((const char*)msg);
			break;
		case wwgmtkMessageType_Error:
			Logger::get().error((const char*)msg);
			break;
		}
	}
}

UWGMNeutralDataAttachPluginCustomizer::~UWGMNeutralDataAttachPluginCustomizer()
{
	if(m_ClientIni != nullptr)
		delete m_ClientIni;
}
