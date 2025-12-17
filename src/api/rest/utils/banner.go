package utils

import "fmt"

func PrintBanner() {
	banner := []string{
		"███████╗ ██████╗ ██████╗  ██████╗",
		"╚══███╔╝██╔═══██╗██╔══██╗██╔═══██╗",
		"  ███╔╝ ██║   ██║██████╔╝██║   ██║",
		" ███╔╝  ██║   ██║██╔══██╗██║   ██║",
		"███████╗╚██████╔╝██║  ██║╚██████╔╝",
		"╚══════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝",
	}

	fmt.Println()
	for _, line := range banner {
		fmt.Println(line)
	}

	fmt.Println()
	fmt.Println("ZoroDB — a tiny vector search engine")
	fmt.Println("Access API at http://localhost:6464")
	fmt.Println()
}
