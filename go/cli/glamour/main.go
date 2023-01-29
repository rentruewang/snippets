package main

import (
	"fmt"

	"github.com/charmbracelet/glamour"
)

func main() {
	in := `# Hello World
	
	This is a simple example of Markdown rendering with Glamour!
	Check out the [other examples](https://github.com/charmbracelet/glamour/tree/master/examples) too.
	
	Bye!
	`

	out, _ := glamour.Render(in, "dark")
	fmt.Print(out)

	fmt.Println()

	// Apparently glamour ignores \r in rendering.

	in = "# Hello World\r\n line 1"

	out, _ = glamour.Render(in, "dark")
	fmt.Println(out)

	fmt.Println()
	in = "# Hello World\n line 1"

	out, _ = glamour.Render(in, "dark")
	fmt.Println(out)
}
