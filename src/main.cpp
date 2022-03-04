#include <format>

namespace {
	void InitializeLog() {
		auto path = logger::log_directory();
		if (!path) {
			util::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format("{}.log"sv, Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
		const auto level = spdlog::level::info;

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);
	}

	void OnEvent(SKSE::MessagingInterface::Message* event) {
		// kDataLoaded
		if (event->type == SKSE::MessagingInterface::kDataLoaded) {
			auto* consoleLog = RE::ConsoleLog::GetSingleton();
			consoleLog->Print("Hello from Example SKSE plugin!");
		}
	}

	std::string_view HelloPapyrus(RE::StaticFunctionTag*, std::string_view text) {
		return std::format("Hi Papyrus, this is C++! You passed the text: '{}'", text);
	}

	bool PapyrusFunctions(RE::BSScript::IVirtualMachine* vm) {
		vm->RegisterFunction("HelloWorld", "MyPapyrusScript", HelloPapyrus);
		return true;
	}
}

// ...
#ifdef SKYRIM_AE
extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;

	v.PluginVersion(Plugin::VERSION);
	v.PluginName(Plugin::NAME);

	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_LATEST });

	return v;
}();
#endif

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
	// ...
	InitializeLog();
	logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());

	// ...
	SKSE::Init(a_skse);

	// ...
	SKSE::GetMessagingInterface()->RegisterListener(OnEvent);

	// ...
	SKSE::GetPapyrusInterface()->Register(PapyrusFunctions);

	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info) {
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Plugin::NAME.data();
	a_info->version = Plugin::VERSION.pack();

	if (a_skse->IsEditor()) {
		return false;
	}

	return true;
}
