#pragma once
#include <iscore/command/SerializableCommand.hpp>

namespace Tutorial
{
/**
 * @brief CommandFactoryName
 * @return A unique key to identify the commands of this plug-in.
 */
inline const CommandParentFactoryKey& CommandFactoryName()
{
    static const CommandParentFactoryKey key{"Tutorial"};
    return key;
}
}