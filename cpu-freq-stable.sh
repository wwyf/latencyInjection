#!/bin/bash
set -x

if [[ -z $(which rdmsr) ]]; then
    echo "msr-tools is not installed. Run 'sudo yum install msr-tools' to install it." >&2
    exit 1
fi

if [[ ! -z $1 && $1 != "enable" && $1 != "disable" ]]; then
    echo "Invalid argument: $1" >&2
    echo ""
    echo "Usage: $(basename $0) [disable|enable]"
    exit 1
fi

#################################
# turbo boost
#################################

# cores=$(cat /proc/cpuinfo | grep processor | awk '{print $3}')
# for core in $cores; do
#     if [[ $1 == "enable" ]]; then
#         wrmsr -p${core} 0x1a0 0x4000850089
#     fi
#     if [[ $1 == "disable" ]]; then
#         wrmsr -p${core} 0x1a0 0x850089
#     fi
#     state=$(rdmsr -p${core} 0x1a0 -f 38:38)
#     if [[ $state -eq 1 ]]; then
#         echo "turbo boost of core ${core}: disabled"
#     else
#         echo "turbo boost of core ${core}: enabled"
#     fi
# done

###############################
# c state
###############################
if [[ $1 == "enable" ]]; then
    # disable some c state
    cpupower -c 0  idle-set -D1
fi

if [[ $1 == "disable" ]]; then
    # enable some c state
    cpupower -c 0  idle-set -E
fi