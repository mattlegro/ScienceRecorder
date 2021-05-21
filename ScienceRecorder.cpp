#include "pch.h"
#include "ScienceRecorder.h"


BAKKESMOD_PLUGIN(ScienceRecorder, "A Plugin to Record Physics Tick Data!", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void ScienceRecorder::onLoad()
{
	_globalCvarManager = cvarManager;
	//cvarManager->log("Plugin loaded!");

	cvarManager->registerCvar(enabledCvarName, "0", "Determines whether Science Recorder is enabled.");

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	cvarManager->log("Hello notifier!");
	//}, "", 0);

	//auto cvar = cvarManager->registerCvar("template_cvar", "hello-cvar", "just a example of a cvar");
	//auto cvar2 = cvarManager->registerCvar("template_cvar2", "0", "just a example of a cvar with more settings", true, true, -10, true, 10 );

	//cvar.addOnValueChanged([this](std::string cvarName, CVarWrapper newCvar) {
	//	cvarManager->log("the cvar with name: " + cvarName + " changed");
	//	cvarManager->log("the new value is:" + newCvar.getStringValue());
	//});

	//cvar2.addOnValueChanged(std::bind(&ScienceRecorder::YourPluginMethod, this, _1, _2));

	// enabled decleared in the header
	//enabled = std::make_shared<bool>(false);
	//cvarManager->registerCvar("TEMPLATE_Enabled", "0", "Enable the TEMPLATE plugin", true, true, 0, true, 1).bindTo(enabled);

	//cvarManager->registerNotifier("NOTIFIER", [this](std::vector<std::string> params){FUNCTION();}, "DESCRIPTION", PERMISSION_ALL);
	//cvarManager->registerCvar("CVAR", "DEFAULTVALUE", "DESCRIPTION", true, true, MINVAL, true, MAXVAL);//.bindTo(CVARVARIABLE);
	//gameWrapper->HookEvent("FUNCTIONNAME", std::bind(&TEMPLATE::FUNCTION, this));
	//gameWrapper->HookEventWithCallerPost<ActorWrapper>("FUNCTIONNAME", std::bind(&ScienceRecorder::FUNCTION, this, _1, _2, _3));
	//gameWrapper->RegisterDrawable(bind(&TEMPLATE::Render, this, std::placeholders::_1));


	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", [this](std::string eventName) {
	//	cvarManager->log("Your hook got called and the ball went POOF");
	//});

	// You could also use std::bind here
	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", std::bind(&ScienceRecorder::YourPluginMethod, this);
	gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", std::bind(&ScienceRecorder::onPhysicsTick, this));
}

void ScienceRecorder::onUnload()
{

}

void ScienceRecorder::pluginEnabledChanged()
{
	const bool enabled = cvarManager->getCvar(enabledCvarName).getBoolValue();

	if (enabled)
	{
		if (!hooked)
		{
			hookMatchStarted();
		}
	}
	else
		if (hooked)
		{
			unhookMatchStarted();
		}
}

void ScienceRecorder::onPhysicsTick()
{

}

void ScienceRecorder::onMatchStart(ServerWrapper server, void* params, std::string eventName)
{

}

void ScienceRecorder::hookMatchStarted()
{
	gameWrapper->HookEventWithCaller<ServerWrapper>(rankedMatchStartedEvent, std::bind(&ScienceRecorder::onMatchStart, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	hooked = true;
}

void ScienceRecorder::unhookMatchStarted()
{
	gameWrapper->UnhookEvent(rankedMatchStartedEvent);
	hooked = false;
}