// Object Dump: writes every Geometry Dash object ID with its sprite frame name, object type,
// hitbox size and flags to objects.jsonl in this mod's save folder. Runs once, at the main menu.
// If GD crashes on some object, just start GD again: the dump resumes after the object that crashed.

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

#include <filesystem>
#include <fstream>
#include <string>

using namespace geode::prelude;

static constexpr int MAX_ID = 6000;  // the highest object ID in 2.2 is a little over 4000

static void runDump() {
    auto dir = Mod::get()->getSaveDir();
    auto dataPath = dir / "objects.jsonl";
    auto progPath = dir / "progress.txt";

    int start = 1;
    if (std::filesystem::exists(progPath)) {
        std::ifstream pf(progPath);
        std::string s;
        pf >> s;
        if (s == "done") {
            return;  // already finished on an earlier launch
        }
        // the id written last is the one being created when GD last stopped: skip it
        start = std::atoi(s.c_str()) + 1;
        log::warn("Object Dump: resuming after id {} (it may have crashed GD)", start - 1);
    }

    auto toolbox = ObjectToolbox::sharedState();
    std::ofstream data(dataPath, std::ios::app);
    int written = 0;

    for (int id = start; id <= MAX_ID; ++id) {
        const char* frame = toolbox->intKeyToFrame(id);
        if (!frame || !frame[0]) {
            continue;  // no such object id
        }
        {   // remember where we are, in case creating this object crashes the game
            std::ofstream pf(progPath, std::ios::trunc);
            pf << id;
        }
        auto obj = GameObject::createWithKey(id);
        if (!obj) {
            continue;
        }
        auto rect = obj->getObjectRect();
        auto size = obj->getContentSize();

        data << "{\"id\":" << id
             << ",\"frame\":\"" << frame << "\""
             << ",\"type\":" << static_cast<int>(obj->m_objectType)
             << ",\"classType\":" << static_cast<int>(obj->m_classType)
             << ",\"zLayer\":" << static_cast<int>(obj->m_defaultZLayer)
             << ",\"zOrder\":" << obj->m_defaultZOrder
             << ",\"width\":" << obj->m_width
             << ",\"height\":" << obj->m_height
             << ",\"radius\":" << obj->m_objectRadius
             << ",\"rectW\":" << rect.size.width
             << ",\"rectH\":" << rect.size.height
             << ",\"contentW\":" << size.width
             << ",\"contentH\":" << size.height
             << ",\"decoration\":" << (obj->m_isDecoration ? 1 : 0)
             << ",\"passable\":" << (obj->m_isPassable ? 1 : 0)
             << ",\"trigger\":" << (obj->m_isTrigger ? 1 : 0)
             << ",\"slopeHazard\":" << (obj->m_slopeIsHazard ? 1 : 0)
             << ",\"ice\":" << (obj->m_isIceBlock ? 1 : 0)
             << "}\n";
        data.flush();
        ++written;
    }

    {
        std::ofstream pf(progPath, std::ios::trunc);
        pf << "done";
    }
    auto path = dataPath.string();
    log::info("Object Dump: wrote {} objects to {}", written, path);
    FLAlertLayer::create(
        "Object Dump finished",
        "Wrote " + std::to_string(written) + " objects to:\n" + path +
            "\n\nSend that file (objects.jsonl) back. You can then disable this mod.",
        "OK")->show();
}

class $modify(DumpMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }
        static bool ran = false;
        if (!ran) {
            ran = true;
            runDump();
        }
        return true;
    }
};
