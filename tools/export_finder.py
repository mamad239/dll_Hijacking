import re
import json
import subprocess
import sys
from colorama import Fore, Back, Style, init
import os

init(autoreset=True)


def check_file_exist(file_path):
    if os.path.exists(file_path):
        return 1
    else:
        return 0


def run_command(command):
    try:
        result = subprocess.run(command, capture_output=True, text=True)
        if result.stderr != '':
            return False
        else:
            return result.stdout
    except FileNotFoundError:
        return False

def extract_founctions(out_command, file_path, pattern):
    lines = out_command.split("\n")
    file_name = (file_path.split("\\")[-1]).split(".")[0]
    line_conter = 0
    print(Fore.GREEN + f"[+]  This is OutPut expot_founctions for {file_name}.dll:" + Fore.GREEN + "\n\n")
    for line in lines:
        match = pattern.match(line)
        if match:
            line_conter += 1
            ordinal, hint, function_name = match.groups()
            export_fanc = function_name
            conter = str(ordinal)
            print(f'#pragma comment(linker,"/export:{export_fanc}={file_name}.{export_fanc},@{conter}")')

    if line_conter == 0:
        return  Fore.RED + "[-]  This DLL is not have export founction!!" + Fore.RESET


def run_main():
    pattern = re.compile(r"\s*(\d+)\s+([0-9A-F]+)\s+[0-9A-F]+\s+([^\s]+)")

    if not sys.argv[1]:
        return Fore.RED + "[-]  Plase enter tour dll path for extract expot founctions!" + Fore.RESET

    if not (run_command(["dumpbin"])):
        return Fore.RED + "[-]  Plase for used this tools install dumpbin and used to PATH!" + Fore.RESET

    file_path = sys.argv[1]
    check_file_out = check_file_exist(file_path)
    if check_file_out == 0:
        return Fore.RED + f"[-]  This DLL Is Not Exist {file_path} Plase Check DLL Path" + Fore.RESET

    command = ["dumpbin", "/exports", file_path]

    out_command = run_command(command)
    if not out_command:
        return Fore.RED + "[-]  Error in rune command!" + Fore.RESET
    else:
        extract_founctions(out_command, file_path, pattern)


if __name__ == "__main__":
    print("\n")
    out = run_main()
    if out:
        print(out)
    print("\n\n")
