#include <glib/gi18n.h>

#include "edatos-config.h"
#include "edatos-application.h"

int
main (int   argc,
      char *argv[])
{
	g_autoptr(EdatosApplication) app = NULL;
	int ret;

	/* Set up gettext translations */
	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	app = edatos_application_new ();

	ret = g_application_run (G_APPLICATION (app), argc, argv);

	return ret;
}
