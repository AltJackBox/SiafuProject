#include <model/SimulationData.h>
#include <utils.h>
#include <fstream>
#include <iostream>

SimulationData SimulationData::getInstance(const std::string pathString)
{
    std::ifstream file{pathString};
    if (!file)
    {
        std::cerr << "The simulation data at " + pathString + " does not exist\n";
        return;
    }
    // if (!givenPath.exists())
    // {
    // 	//throw new RuntimeException("The simulation data at " + pathString + " does not exist");
    // }
    if (ends_with(pathString, ".jar"))
    {
        //return new JarSimulationData(givenPath);
    }
    else
    {
        std::cerr << "Invalid simulation data (" + pathString + "). Please provide a supported type " + "(currently a folder or jar file\n";
        //throw new RuntimeException("Invalid simulation data (" + pathString + "). Please provide a supported type " + "(currently a folder or jar file");
    }
}

// Look for rapidXML
// Class < ? extends BaseAgentModel > getAgentModelClass()
// {
//     try
//     {
//         return Class.forName(simulationConfig
//                                  .getString("models.agentmodel"),
//                              true, classLoader)
//             .asSubclass(BaseAgentModel.class);
//     }
//     // catch (Exception e)
//     // {
//     //     throw new RuntimeException(e);
//     // }
// }

// Class < ? extends BaseContextModel > getContextModelClass()
// {
//     try
//     {
//         return Class.forName(simulationConfig
//                                  .getString("models.contextmodel"),
//                              true, classLoader)
//             .asSubclass(BaseContextModel.class);
//     }
//     catch (Exception e)
//     {
//         throw new RuntimeException(e);
//     }
// }

// Class < ? extends BaseWorldModel > getWorldModelClass()
// {
//     try
//     {
//         return Class.forName(simulationConfig
//                                  .getString("models.worldmodel"),
//                              true, classLoader)
//             .asSubclass(BaseWorldModel.class);
//     }
//     catch (Exception e)
//     {
//         throw new RuntimeException(e);
//     }
// }

// HashMap<std::string, InputStream> getPlaceFiles()
// {
//     return getFilesByPath(PLACES_PATH);
// }

// HashMap<String, InputStream> getOverlayFiles()
// {
//     return getFilesByPath(OVERLAYS_PATH);
// }

// InputStream getWallsFile()
// {
//     return getFile(WALLS_FILE);
// }

// XMLConfiguration getConfigFile()
// {
//     if (simulationConfig == null)
//     {
//         simulationConfig = new XMLConfiguration();
//         try
//         {
//             simulationConfig.load(getFile(CONFIG_FILE));
//         }
//         catch (ConfigurationException e)
//         {
//             throw new RuntimeException(
//                 "Error reading the simulation config file", e);
//         }
//     }
//     return simulationConfig;
// }

// SimulationData(final File givenPath)
// {
//     try
//     {
//         classLoader =
//             new URLClassLoader(new URL[]{givenPath.toURI()
//                                              .toURL()});
//     }
//     catch (MalformedURLException e)
//     {
//         // TODO Auto-generated catch block
//         e.printStackTrace();
//     }
// }