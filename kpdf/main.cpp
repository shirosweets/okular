/***************************************************************************
 *   Copyright (C) 2002 by Wilco Greven <greven@kde.org>                   *
 *   Copyright (C) 2003 by Christophe Devriese                             *
 *                         <Christophe.Devriese@student.kuleuven.ac.be>    *
 *   Copyright (C) 2003 by Laurent Montel <montel@kde.org>                 *
 *   Copyright (C) 2003-2004 by Albert Astals Cid <tsdgeos@terra.es>       *
 *   Copyright (C) 2004 by Andy Goossens <andygoossens@telenet.be>         *
 *   Copyright (C) 2004 by Stephan Binner <binner@kde.org>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "kpdf_shell.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
I18N_NOOP("kpdf, a kde pdf viewer based on xpdf");

static const char version[] = "v0.4";

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP("Document to open"), 0 },
    KCmdLineLastOption
};

int main(int argc, char** argv)
{
    KAboutData about(
        "kpdf",
        I18N_NOOP("KPDF"),
        version,
        description,
        KAboutData::License_GPL,
        "(C) 2002 Wilco Greven, Christophe Devriese");

    about.addAuthor("Wilco Greven", 0, "greven@kde.org");
    about.addAuthor("Christophe Devriese", 0, "oelewapperke@oelewapperke.org");
    about.addAuthor("Laurent Montel", 0, "montel@kde.org");
    about.addAuthor("Albert Astals Cid", I18N_NOOP("xpdf 3.0 integration, thumbnails"), "astals11@terra.es");

    about.addCredit("Derek Noonburg", I18N_NOOP("Xpdf author"), 0, "http://www.foolabs.com/xpdf/");

    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;

    // see if we are starting with session management
    if (app.isRestored())
    {
        RESTORE(KPDF::Shell);
    } else {
        // no session.. just start up normally
        KCmdLineArgs* args = KCmdLineArgs::parsedArgs();

        if (args->count() == 0)
        {
            KPDF::Shell* widget = new KPDF::Shell;
            widget->show();
        }
        else
        {
            for (int i = 0; i < args->count(); ++i)
            {
                KPDF::Shell* widget = new KPDF::Shell;
                widget->show();
                widget->openURL(args->url(i));
            }
        }
        args->clear();
    }

    return app.exec();
}

// vim:ts=2:sw=2:tw=78:et
