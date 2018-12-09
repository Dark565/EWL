#!/bin/bash

###################
##    AUTOGEN 	 ##
###################

### Bash configuration

shopt -s expand_aliases

### Library configuration's arrays of labels

CONFIG_BEGINNING_HINT=\
"\
#######################
## EWL CONFIGURATION ##
#######################
#
# Leave the variable empty or set it to 'auto' to determine its value automatically
"

HINT_TARGET=\
"\
# Define an output platform:
#	> linux
#	> win32
#	> macos
#	> android
"

HINT_ARCH=\
"\
# Define a bit architecture:
#	> 32
#	> 64
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
# Define libraries linking method for each submodule in the case when 'manual' for CONFIG_GLOBAL_LOAD was choosen
#	> link
#	> load
"

CONFIG_LABELS=(\
\
CONFIG_TARGET \
CONFIG_ARCH \
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
HINT_TARGET \
HINT_ARCH \
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

### Configuration ###

config_file=.config

### Functions ###


function writeTab() { #arg: tab file opt

	eval tab=( '${'$1'[@]}' )
	local i

	if [[ ${#tab[@]} != 0 ]] && [[ "$2" != "" ]]; then

		if [[ "$3" != "" ]]; then printf "$3" >>"$2"; fi

		for i in ${tab[@]}; do
			printf "$i\n" >>"$2"
		done

		return 0

	fi

	return 1

}

function GenerateConfig() {

	printf "${CONFIG_BEGINNING_HINT}" >${config_file}

	for i in ${!CONFIG_LABELS[@]}
	do
	
		local curr_l=${CONFIG_LABELS[i]}	

		if [ ! -z "${!curr_l}" ]; then
			local set_val="${!curr_l}"
		else
			local set_val="${CONFIG_DEF_VALS[i]}"
			eval ${curr_l}=${set_val}
		fi

		printf "\n${CONFIG_LABELS[i]}=${set_val}" >>"${config_file}"

		if [[ ${CONFIG_HINTS[i]} != "" ]]; then
			local hnt_text="${!CONFIG_HINTS[i]}"

			if [[ "${hnt_text}" != "" ]]; then
				printf "\n${hnt_text}" >>${config_file}
			fi
		fi

	done

	return 0
}

function LoadFixedConf() {

	if [ -f ${config_file} ]; then
		source ${config_file}
	fi
	GenerateConfig
	return 0
}

function GenerateBuildEnv() {
	LoadFixedConf
}

case ${1} in

"-h" | "--help")
	printf \
"Ever-Word Library's autogen script\n\
\n\
Executing the script without arguments creates makefile based on options chosen in \'${config_file}\'.\nIn the reason, when \'${config_file}\' is missing, this creates it;\n\
-g | --generate => generates makefile based on \'${config_file}\' set;\n
-o | --in-order => generates \'${config_file}\' or makefile if first file is already done
-n | --new-config => creates a new ${config_file} file;\n\
-c | --complete-config => Completes the \'${config_file}\' with missing labels or creates new if it is missing;
-f | --function => calls to the script function;\n\
-h | --help => prints this help;\n\n"

	exit 0
	;;

"-f" | "--function")
	if [[ ${2} != "" ]]; then
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

"-g" | "--generate" | "")
	
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

"-o" | "")
	if [ -f "${config_file}" ]; then
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
