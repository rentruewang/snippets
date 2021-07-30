package main

import (
	"fmt"

	"github.com/charmbracelet/lipgloss"
)

func main() {
	style := lipgloss.NewStyle().
		Bold(true).
		Foreground(lipgloss.Color("#FAFAFA")).
		Background(lipgloss.Color("#7D56F4")).
		PaddingTop(2).
		PaddingLeft(4).
		Width(22)

	fmt.Println(style.Render("Hello, kitty."))
	fmt.Println()
	// This will not work well.
	fmt.Println(style.Render("Hello, kitty."), style.Render("Hello, kitty."))
	block := lipgloss.PlaceHorizontal(80, lipgloss.Center, style.Render("Hello, kitty."))
	fmt.Print(block)
	block = lipgloss.PlaceHorizontal(80, lipgloss.Center, style.Render("Hello, kitty."))
	fmt.Print(block)

	styleA := lipgloss.NewStyle().
		Foreground(lipgloss.Color("229")).
		Background(lipgloss.Color("63"))

	styleB := lipgloss.NewStyle().
		Foreground(lipgloss.Color("201")).
		Inherit(styleA)

	fmt.Println(styleA.Render("a"), styleB.Render("b"))
	fmt.Println(styleA.Render("a"))
	fmt.Println(styleB.Render("b"))
}
