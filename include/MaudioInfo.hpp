/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_INFO
#define MAUDIO_INFO


namespace maudio{

#ifndef MAUDIO_GIT_BRANCH
	#define MAUDIO_GIT_BRANCH "unknown"
#endif

#ifndef MAUDIO_GIT_COMMIT
	#define MAUDIO_GIT_COMMIT "unknown"
#endif

#ifndef MAUDIO_GIT_DESCRIPTION
	#define MAUDIO_GIT_DESCRIPTION "unknown"
#endif
	
#ifndef MAUDIO_VERSION
	#define MAUDIO_VERSION "v0.0.0"
#endif

const char *getGitBranch();
const char *getGitCommit();
const char *getGitDescription();
const char *getVersionString();
int getVersionMajor();
int getVersionMinor();
int getVersionPatch();

} // maudio

#endif // MAUDIO_INFO




