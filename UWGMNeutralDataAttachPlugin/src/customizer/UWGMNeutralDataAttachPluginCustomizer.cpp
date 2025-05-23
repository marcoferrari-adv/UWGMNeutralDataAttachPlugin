#include "pch.hpp"

#include "UWGMNeutralDataAttachPluginCustomizer.hpp"
#include "listeners/UWGMNeutralDataAttachPluginSaveListener.hpp"
#include "configuration/UWGMClientIni.hpp"
#include "utilities/StopWatch.hpp"

UWGMNeutralDataAttachPluginCustomizer::UWGMNeutralDataAttachPluginCustomizer()
	: m_ClientIni(UWGMClientIni::getInstance())
{
}

xint UWGMNeutralDataAttachPluginCustomizer::initialize(wwgmtkClient_ptr client)
{

#if !defined(DISTRIBUTION)
	StopWatch sw;
	sw.start();
#endif

	m_Client = client;
	this->showMessage("UWGMNeutralDataAttachPlugin Application initialize", wwgmtkMessageType_Info);

#if DEBUG
	std::wstring iniMap = m_ClientIni->dumpIniMap();
	this->showMessage(xstring::Printf("UWGM client init map is %ls ", iniMap.c_str()), wwgmtkMessageType_Info);
#endif

	std::wstring neutralDataConfiguiredValue = m_ClientIni->readProperty(L"SolidWorks", L"upload.autoattach.searchpath");

#if DEBUG
	this->showMessage(xstring::Printf("UWGM client upload property is %ls ", neutralDataConfiguiredValue.c_str()), wwgmtkMessageType_Info);
#endif

	if (neutralDataConfiguiredValue.empty())
	{
		this->showMessage("upload.autoattach.searchpath not configured in wgmclient.ini, no neutral data attach will be perfomed", wwgmtkMessageType_Error);
		return wwgmtkError_NoError;
	}

	vector<std::wstring> neutralDataPaths = UWGMClientIni::getMultiValueTokens(neutralDataConfiguiredValue);
	if (neutralDataPaths.empty())
	{
		this->showMessage("Unable to evaluate neutral data paths", wwgmtkMessageType_Error);
		return wwgmtkError_NoError;
	}

	wwgmtkWorkspaceSaveListener_ptr wsListener = new UWGMNeutralDataAttachPluginSaveListener(this, neutralDataPaths);
	wwgmtkWorkspaceOperationsRegistry_ptr wsOpRegistry = m_Client->getWorkspaceOperationsRegistry();
	wsOpRegistry->registerSaveListener(wsListener);
	this->showMessage("CleanUWGMNeutralDataFolder save listener registered", wwgmtkMessageType_Info);

#if !defined(DISTRIBUTION)
	this->showMessage(xstring::Printf("CleanUWGMNeutralDataFolder inzialization took %f ms", sw.elapsedMilliseconds()), wwgmtkMessageType_Info);
#endif
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

void UWGMNeutralDataAttachPluginCustomizer::showMessage(xstring msg, xint msgType, xbool saveLog)
{
	if (msg.IsNull() || msg.IsEmpty())
		return;

	wwgmtkClientWindow_ptr tkWin = m_Client->getTopWindow();
	tkWin->showMessage(msg, msgType);
}

UWGMNeutralDataAttachPluginCustomizer::~UWGMNeutralDataAttachPluginCustomizer()
{
	if(m_ClientIni != nullptr)
		delete m_ClientIni;
}
