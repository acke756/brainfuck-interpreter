#pragma once

#define ANSI_RST "\033[0m"

#define ANSI_BLD "\033[1m"
#define ANSI_UNL "\033[4m"
#define ANSI_NOT_BLD "\033[22m"
#define ANSI_NOT_UNL "\033[24m"

#define ANSI_FG_BLK "\033[30m"
#define ANSI_FG_RED "\033[31m"
#define ANSI_FG_GRN "\033[32m"
#define ANSI_FG_YLW "\033[33m"
#define ANSI_FG_BLU "\033[34m"
#define ANSI_FG_MAG "\033[35m"
#define ANSI_FG_CYN "\033[36m"
#define ANSI_FG_WHT "\033[37m"
#define ANSI_FG_RST "\033[39m"

#define ANSI_BG_BLK "\033[40m"
#define ANSI_BG_RED "\033[41m"
#define ANSI_BG_GRN "\033[42m"
#define ANSI_BG_YLW "\033[43m"
#define ANSI_BG_BLU "\033[44m"
#define ANSI_BG_MAG "\033[45m"
#define ANSI_BG_CYN "\033[46m"
#define ANSI_BG_WHT "\033[47m"
#define ANSI_BG_RST "\033[49m"

#define ANSI_CUU(n) "\033[" #n "A"
#define ANSI_CUD(n) "\033[" #n "B"
#define ANSI_CUF(n) "\033[" #n "C"
#define ANSI_CUB(n) "\033[" #n "D"
#define ANSI_CNL(n) "\033[" #n "E"
#define ANSI_CPL(n) "\033[" #n "F"
#define ANSI_CHA(n) "\033[" #n "G"
#define ANSI_CUP(n,m) "\033[" #n ";" #m "H"
#define ANSI_ED(n) "\033[" #n "J"
#define ANSI_EL(n) "\033[" #n "K"
#define ANSI_SU(n) "\033[" #n "S"
#define ANSI_SD(n) "\033[" #n "T"
