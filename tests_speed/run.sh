#!/usr/bin/env bash

set -e

BOLD="\033[1m"
RESET="\033[0m"
LIGHT_RED="\033[91m"
LIGHT_GREEN="\033[92m"
LIGHT_CYAN="\033[96m"


DEFAULT_SEED=42

logging(){
	local type=$1; shift
	printf "${LIGHT_CYAN}${BOLD}$0${RESET} [%b] : %b\n" "$type" "$*"
}
log_info(){
	logging "${LIGHT_GREEN}info${RESET}" "$@"
}
log_error(){
	logging "${LIGHT_RED}error${RESET}" "$@" >&2
}

execute_speed_test()
{
	START=$(date +%s.%N)
	time  > /dev/null 2>&1 "$1" "$2" 
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	echo "$DIFF sec"
}


show_help(){
cat <<EOF
Usage :
$0              Default seed is 42
$0 [seed]     	Set the seed to be used in benchmark
EOF
}

parse_args(){
	case "$1" in
		--help | -h)
			show_help
			exit 0;;
		"") 
			log_info "No seed provided, falling back to default seed '$DEFAULT_SEED'"
			return;;
		*)	return;;
	esac
}

main(){
	cd $(dirname $0)
	make fclean > /dev/null
	make NS_NAME=ft
	mv a.out speed_ft
	make fclean > /dev/null

	make NS_NAME=std
	mv a.out speed_std
	make fclean > /dev/null

	local seed="${1:-$DEFAULT_SEED}"
	parse_args "$@"
	log_info "Seed: $seed"
	log_info "Benching std..."
	execute_speed_test ./speed_std $seed
	execute_speed_test ./speed_std $seed
	execute_speed_test ./speed_std $seed
	execute_speed_test ./speed_std $seed
	
	log_info "Benching ft..."
	execute_speed_test ./speed_ft $seed
	execute_speed_test ./speed_ft $seed
	execute_speed_test ./speed_ft $seed
	execute_speed_test ./speed_ft $seed

}

main "$@"