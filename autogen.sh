###################
##    AUTOGEN 	 ##
###################

### Bash configuration

shopt -s expand_aliases

### Library configuration's arrays of labels

CONFIG_BEGINNING_HINT=\
"\
#######################\n\
## EWL CONFIGURATION ##\n\
#######################\n\
#\n\
# Leave the variable empty or set it to 'auto' to determine its value automatically\n\
\n\
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
"#=> (win32, unix, macos, android) <=#" \
"#=> (i386, amd64, arm, aarm64) <=#" \
\
"\n\
# Method for placing library's shared object\n\
#\n\
# separated => An object for each module\n\
# merged => Instead of the above, merge all objects into one common\n\
\n\
#=> (separated, merged) <=#" \
\
"\n\
# Method for linking dynamic libraries for each module\n\
\n\
#=> (link, load, manual) <=#" \
\
"\n\
# Below there are configuration labels valid in the reason when 'CONFIG_GLOBAL_LOAD=manual' was chosen\n\
\n\
#=> (link, load) <=#" \
"" \
"#" \
)

CONFIG_DEF_VALS=(\
\
auto \
auto \
separated \
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

function GenerateConfig() {

	if [ -f "${config_file}" ]; then
		rm "${config_file}"
	fi

	printf "${CONFIG_BEGINNING_HINT}" >> "${config_file}"


	for i in ${!CONFIG_LABELS[@]}
	do

		if [[ "${CONFIG_HINTS[i]}" != "" ]]; then
			printf "\n${CONFIG_HINTS[i]}" >> "${config_file}"
		fi
	
		local curr_l=${CONFIG_LABELS[i]}	

		if [ ! -z "${!curr_l}" ]; then
			local set_val="${!curr_l}"
		else
			local set_val="${CONFIG_DEF_VALS[i]}"
			eval ${curr_l}=${set_val}
		fi

		printf "\n${CONFIG_LABELS[i]}=${set_val}" >> "${config_file}"

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
