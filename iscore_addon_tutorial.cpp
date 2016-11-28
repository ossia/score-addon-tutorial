#include "iscore_addon_tutorial.hpp"
#include <iscore_addon_tutorial_commands_files.hpp>

#include <Tutorial/Process/TutorialProcessFactory.hpp>
#include <Tutorial/Process/Executor/TutorialProcessExecutor.hpp>
#include <Tutorial/Process/Inspector/TutorialProcessInspector.hpp>
#include <Tutorial/Process/LocalTree/TutorialProcessLocalTree.hpp>
#include <Tutorial/Process/Layer/TutorialProcessLayerFactory.hpp>
#include <Tutorial/ApplicationPlugin/TutorialApplicationPlugin.hpp>
#include <Tutorial/DocumentPlugin/TutorialDocumentPlugin.hpp>

#include <iscore/plugins/customfactory/FactorySetup.hpp>

iscore_addon_tutorial::iscore_addon_tutorial()
{

}

iscore_addon_tutorial::~iscore_addon_tutorial()
{

}

/**
 * @brief iscore_addon_tutorial::version
 * @return The version of the plug-in
 */
iscore::Version iscore_addon_tutorial::version() const
{
    return iscore::Version{0};
}

/**
 * @brief iscore_addon_tutorial::key
 * @return A unique identifier for the plug-in
 */
UuidKey<iscore::Plugin> iscore_addon_tutorial::key() const
{
    // Can be generated with "uuidgen" on linux or OS X.
    return_uuid("e8601d50-e29e-4437-8c65-fcee42655a0b");
}

/**
 * @brief iscore_addon_tutorial::required
 * @return Features that this plug-in requires.
 */
QStringList iscore_addon_tutorial::required() const
{
    return {};
}

/**
 * @brief iscore_addon_tutorial::offered
 * @return Features that this plug-in provides.
 */
QStringList iscore_addon_tutorial::offered() const
{
    return {};
}

/**
 * @brief iscore_addon_tutorial::updateSaveFile
 * This function is called if someone tries to load
 * a save file that was created with a previous version
 * of this plug-in.
 * This allows to update the JSON data in order to load
 * it in the current version.
 */
void iscore_addon_tutorial::updateSaveFile(
        QJsonObject& obj,
        iscore::Version obj_version,
        iscore::Version current_version)
{

}

/**
 * @brief iscore_addon_tutorial::factoryFamilies
 * This function allows the plug-in to provide new factory types.
 * All plug-ins will be scanned for factories of the provided type.
 *
 * For instance, a new interface to display some elements in a toolbar.
 */
std::vector<std::unique_ptr<iscore::FactoryListInterface> >
iscore_addon_tutorial::factoryFamilies()
{
    return {};
}


/**
 * @brief iscore_addon_tutorial::factories
 *
 * This function allows the plug-in to provide implementations for the
 * factory types provided earlier.
 *
 * For instance, factories for the elements that will go in the toolbar.
 */
std::vector<std::unique_ptr<iscore::FactoryInterfaceBase> >
iscore_addon_tutorial::factories(
        const iscore::ApplicationContext& ctx,
        const iscore::AbstractFactoryKey& key) const
{
    return instantiate_factories<
            iscore::ApplicationContext,
    TL<
        FW<Process::ProcessModelFactory,
           Tutorial::ProcessFactory>,
        FW<Process::LayerFactory,
           Tutorial::LayerFactory>,
        FW<Process::InspectorWidgetDelegateFactory,
           Tutorial::InspectorFactory>,
        FW<Engine::Execution::ProcessComponentFactory,
           Tutorial::ProcessExecutorComponentFactory>,
        FW<Engine::LocalTree::ProcessComponentFactory,
           Tutorial::LocalTreeProcessComponentFactory>,
        FW<iscore::DocumentPluginFactory,
           Tutorial::DocumentPluginFactory>
    >>(ctx, key);
}

/**
 * @brief iscore_addon_tutorial::make_applicationPlugin
 *
 * This function allows to instantiate an application-wide object.
 * These objects are instantiated before any factory.
 */
iscore::GUIApplicationContextPlugin*
iscore_addon_tutorial::make_applicationPlugin(
        const iscore::GUIApplicationContext& app)
{
    return new Tutorial::ApplicationPlugin{app};
}

/**
 * @brief iscore_addon_tutorial::make_commands
 * This function provides the list of commands available with this
 * plug-in.
 */
std::pair<const CommandParentFactoryKey, CommandGeneratorMap>
iscore_addon_tutorial::make_commands()
{
    using namespace Tutorial;
    std::pair<const CommandParentFactoryKey, CommandGeneratorMap> cmds{CommandFactoryName(), CommandGeneratorMap{}};

    using Types = TypeList<
#include <iscore_addon_tutorial_commands.hpp>
      >;
    for_each_type<Types>(iscore::commands::FactoryInserter{cmds.second});

    return cmds;
}
