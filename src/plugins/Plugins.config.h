/* ---------------------------------------------------------------------------------------------------------------------------------
 * User plugins for OCS
 *
 * For each entery below one must specify the class instance name and #include the class header file.
 *
 * Each plugin should have a directory that contains all of its files, which gets dropped into to the /src/plugins directory.
 * The plugin main class instance name should match the directory name.
 * The plugin main class must have a "void init();" method for OCS to call when it starts up.
 * 
 * ---------------------------------------------------------------------------------------------------------------------------------
*/

// =================================================================================================================================

// *** Comment out PLUGIN1 above AND uncomment the following two lines to enable the sample plugin ***
//#define PLUGIN1                    sample //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "sample/Sample.h"                //         Specify the header file to include the class.

#define PLUGIN1                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin1/Name.h"               //         Specify the header file to include the class.
#define PLUGIN1_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN2                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin2/Name.h"               //         Specify the header file to include the class.
#define PLUGIN2_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN3                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin3/Name.h"               //         Specify the header file to include the class.
#define PLUGIN3_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN4                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin4/Name.h"               //         Specify the header file to include the class.
#define PLUGIN4_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN5                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin5/Name.h"               //         Specify the header file to include the class.
#define PLUGIN5_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN6                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin6/Name.h"               //         Specify the header file to include the class.
#define PLUGIN6_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN7                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin7/Name.h"               //         Specify the header file to include the class.
#define PLUGIN7_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN8                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin8/Name.h"               //         Specify the header file to include the class.
#define PLUGIN8_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing
