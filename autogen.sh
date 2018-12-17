#!/bin/bash

###################
##    AUTOGEN 	 ##
###################


### Project's preconfig ###

PROJECT_CONFIG_FILE=".config"

PROJECT_NAME=(\
\
"Ever-Word Library" \
"Qer-Library" )

PROJECT_VERSION=(\
\
"Alpha" )

PROJECT_HELP=\
"\
${PROJECT_NAME[0]}'s autogen script

Executing the script without arguments creates makefile based on options chosen in \'${PROJECT_CONFIG_FILE}\'.\nIn the reason, when \'${PROJECT_CONFIG_FILE}\' is missing, this creates it;
-g | --generate => generates makefile based on \'${PROJECT_CONFIG_FILE}\' set;
-o | --in-order => generates \'${PROJECT_CONFIG_FILE}\' or makefile if first file is already done
-n | --new-config => creates a new ${PROJECT_CONFIG_FILE} file;
-c | --complete-config => Completes the \'${PROJECT_CONFIG_FILE}\' with missing labels or creates new if it is missing;
-f | --function => calls to the script function;
-h | --help => prints this help;

"

### Project's build script ###

CONFIG_BEGINNING_HINT=\
"\
#######################
## EWL CONFIGURATION ##
#######################
#
# Leave the variable empty or set it to 'auto' to determine its value automatically
"

HINT_COMPILER=\
"\
# Define the compiler
#	> ...
"

HINT_TARGET=\
"\
# Define an output platform:
#	> linux
#	> win32
#	> macos
#	> android
"

HINT_LIBFORMAT=\
"\
# Define shared objects' compiling method:
#	> separate
#	> merge
"

HINT_GLOBLOAD=\
"\
# Define how to link submodules' libraries:
#	> manual
#	> link
#	> load
"

HINT_FLIBOGG=\
"\
# Define libraries linking method for each submodule in the case when 'manual' for CONFIG_GLOBAL_LOAD was chosen
#	> link
#	> load
"

CONFIG_LABELS=(\
\
CONFIG_COMPILER \
CONFIG_TARGET \
CONFIG_LIBRARY_FORMAT \
CONFIG_GLOBAL_LOAD \
CONFIG_UNIX_GRAPH_LIBX11_LOAD \
CONFIG_UNIX_GRAPH_LIBXRANDR_LOAD \
CONFIG_FORMS_LIBTIFF_LOAD \
CONFIG_FORMS_LIBPNG_LOAD \
CONFIG_FORMS_LIBOGG_LOAD \
)

CONFIG_HINTS=(\
\
HINT_COMPILER \
HINT_TARGET \
HINT_LIBFORMAT \
HINT_GLOBLOAD \
HINT_UGLIBX11 \
HINT_UGLIBXRANDR \
HINT_FLIBTIFF \
HINT_FLIBPNG \
HINT_FLIBOGG \
)

CONFIG_DEF_VALS=(\
\
auto \
auto \
separate \
manual \
link \
link \
load \
load \
load \
load \
)

CONFIG_PROCEDURE=\
\
CONFIG_MK_PROC

### Functions ###

#Find program in directories specified by variable in PATH format
findProgram() { #args: program, variable
	local SEARCH_DIR
	local ITERATION=1

	while true; do
		local SEARCH_DIR=$(echo "$2" | cut -d":" -f"$ITERATION")
		local ITERATION=$((ITERATION+1))

		if test "${SEARCH_DIR}" != ""; then
	
			if test -x "${SEARCH_DIR}/$1"; then
				return 0
			fi
		else
			break
		fi

	done

	return 1
}
#Write array columns pointed by its name to file
writeArray() { #args: tab file opt

	eval tab=( '${'$1'[@]}' )
	local i

	if test ${#tab[@]} != 0 && test "$2" != ""; then

		if test "$3" != ""; then printf "$3" >>"$2"; fi

		for i in ${tab[@]}; do
			printf "$i\n" >>"$2"
		done

		return 0

	fi

	return 1

}

GenerateConfig() {

	printf "${CONFIG_BEGINNING_HINT}" >${PROJECT_CONFIG_FILE}

	for i in ${!CONFIG_LABELS[@]}
	do
	
		local curr_l=${CONFIG_LABELS[i]}	

		if ! test -z "${!curr_l}"; then
			local set_val="${!curr_l}"
		else
			local set_val="${CONFIG_DEF_VALS[i]}"
			eval ${curr_l}=${set_val}
		fi

		printf "\n${CONFIG_LABELS[i]}=${set_val}" >>"${PROJECT_CONFIG_FILE}"

		if test ${CONFIG_HINTS[i]} != ""; then
			local hnt_text="${!CONFIG_HINTS[i]}"

			if test "${hnt_text}" != ""; then
				printf "\n${hnt_text}" >>${PROJECT_CONFIG_FILE}
			fi
		fi

	done

	return 0
}

LoadFixedConf() {

	if test -f ${PROJECT_CONFIG_FILE}; then
		. ${PROJECT_CONFIG_FILE}
	fi
	GenerateConfig
	return 0
}


YELLOW="\033[1;33m"
RED="\033[0;31m"
GREEN="\033[0;32m"
NOCOLOR="\033[0m"


CONF_SAVED=""
APT_EXISTS=""
PRECOMMAND=""

tryInstall() { #args: dependence_name

	if ! test -z "${APT_EXISTS}" || findProgram "apt" "$PATH"; then

		APT_EXISTS=1

		if test -z "${PRECOMMAND}" && test "$(id -u)" != "0" && findProgram "sudo" "$PATH"; then
			PRECOMMAND="sudo"
		fi

		local confirmation

		if ! test -z "${CONF_SAVED}";
		then
			confirmation="${CONF_SAVED}"
		else
			
			printf "${GREEN}Try it now?${NOCOLOR} (yes[y]/no[n]/always[yy]/never[nn])\n"
			read confirmation
		fi

		case "${confirmation}" in
			"yy" | "always" )
				CONF_SAVED="y"
				confirmation="y"
				;;
			"nn" | "never" )
				CONF_SAVED="n"
				confirmation="n"
				;;
		esac

		case "${confirmation}" in
			"y" | "yes" )
				if ${PRECOMMAND} apt install -y "$1"
				then
					printf "\n${GREEN}Instalation ended with success!${NOCOLOR}\n\n"
				else
					printf "\n${YELLOW}Installation ended with error!${NOCOLOR}\n\n"
				fi
				;;
		esac

	fi
}

warningDependence() { #args: dependence_name

	printf \
"\n${YELLOW}Warning!${NOCOLOR}
'${YELLOW}$1${NOCOLOR}'${NOCOLOR} - a program necessary to build the project, not found
You can try to install this from a repository by writing eg. \`sudo apt install \"$1\"\`.\n\n"

	
	tryInstall "$1"

	return 0
}

reportDependences() { #args: program_name ...
	local err=0
	local i
	for i in $(seq 1 $#); do
		if ! findProgram "${!i}" "$PATH"; then
			warningDependence "${!i}"
			eval "NODEP_${!i}"=1
			err=1
		fi
	done
	return ${err}
}

reportText() { #args: text possibles ...

	for i in $(seq 2 $#); do
		if test "${1}" == "${!i}"; then
			return 0
		fi
	done

	return 1

}

reportGrep() { #args: text possibles ...

	for i in $(seg 2 $#); do
		if echo "$1" | grep ${!i} >/dev/null; then
			return 0
		fi
	done
	return 1
}

CONFIG_PREPPROC_COMPILER() {
	if ! reportText "${CONFIG_COMPILER}" \
		"auto"
	then
		if ! test -x "${CONFIG_COMPILER}"; then
			printf "\n# Cannot find '"${CONFIG_COMPILER}"'\n# Looking for gcc\n\n" 1>&2
				
		else
			return 0
		fi
	fi

	if reportDependences \
		"gcc"
	then
		CONFIG_COMPILER="gcc"
	fi


}

CONFIG_PREPPROC_TARGET() {	
	if ! reportText "${CONFIG_TARGET}" \
			"win32" \
			"linux" \
			"macos" \
			"android"
	then #when 'auto' or whatever

		if test -z "${NODEP_gcc}"; then
			local SYS_NAME="$("${CONFIG_COMPILER}" -dumpmachine | sed 's/^.*-\{1\}\(.*\)/\1/g')"
		else
			printf "\n# No gcc accessible\n# Detecting target from system\n\n" 1>&2

			local SYS_NAME="$(uname -o)"
			if test $? != 0; then
				SYS_NAME="$(uname -s)"
			fi
		fi

		case "${SYS_NAME}" in
			"MS/Windows" | "Msys" | "mingw32" )
				CONFIG_TARGET="win32"
				;;
			"Darwin" | "darwin" )
				CONFIG_TARGET="macos"
				;;
			"Android" | "android" ) 
				CONFIG_TARGET="android"
				;;
			* )
				CONFIG_TARGET="linux"
				;;
		esac
	fi

	return 0
}

CONFIG_PREPPROC_LIBRARY_FORMAT() {
	if ! reportText "${CONFIG_LIBRARY_FORMAT}" \
		"separate" \
		"merge"
	then
		CONFIG_LIBRARY_FORMAT="separate"
	fi

	return 0
}

CONFIG_PREPPROC_GLOBLOAD() {	
	if ! reportText "${CONFIG_GLOBAL_LOAD}" \
		"manual" \
		"link" \
		"load"
	then
		CONFIG_GLOBAL_LOAD="manual"
	fi

	return 0
}

CONFIG_PREPPROC_MASTER_LIBRARY() {

	if ! reportText "${!1}" \
		"link" \
		"load"
	then
		eval "${!1}"="link"

	fi
	return 0
}

CONFIG_PREPARE_PROCS=(\
\
CONFIG_PREPPROC_COMPILER \
CONFIG_PREPPROC_TARGET \
CONFIG_PREPPROC_LIBRARY_FORMAT \
CONFIG_PREPPROC_GLOBLOAD \
CONFIG_PREPPROC_MASTER_LIBRARY \
)

CONFIG_PREPARE_VARS() {

	local i
	for i in ${!CONFIG_LABELS[@]}; do
		local func
		if test $i -lt ${#CONFIG_PREPARE_PROCS[@]}; then
			func=${CONFIG_PREPARE_PROCS[i]}
		else
			local l_index=$((${#CONFIG_PREPARE_PROCS[@]}-1))
			func=${CONFIG_PREPARE_PROCS[l_index]}
		fi
		${func} ${CONFIG_LABELS[i]}
	done

	return 0

}

CONFIG_MK_PROC() {

	CONFIG_PREPARE_VARS

	echo "Compiler: ${CONFIG_COMPILER}"
	echo "Target: ${CONFIG_TARGET}"

	return 0

}

GenerateBuildEnv() {
	LoadFixedConf

	reportDependences \
		"make"

	"${CONFIG_PROCEDURE}"

	return 0
}

case ${1} in

"-h" | "--help")
	printf "${PROJECT_HELP}"
	exit 0
	;;

"-f" | "--function")
	if test "${2}" != ""; then
		if declare -f ${2} > /dev/null; then
			f_arguments="$(echo "$@" | cut -d' ' -f3-)"
			${2} ${f_arguments}
			exit $?
		else
			printf "This function doesn't exist\n" >&2
		fi
	else
		printf "You have to specify a function name\n" >&2
	fi
	;;

"-g" | "--generate")
	
	GenerateBuildEnv
	exit 0
	;;

"-n" | "--new-config")

	GenerateConfig
	exit 0
	;;

"-c" | "--complete-config")

	LoadFixedConf
	exit 0
	;;

"-o" | "--in-order" | "")
	if test -f "${PROJECT_CONFIG_FILE}"; then
		GenerateBuildEnv
	else
		GenerateConfig
	fi
	exit 0
	;;

*)
	printf "Invalid argument\n" >&2
	;;

esac

exit 1
