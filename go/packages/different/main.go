// Using a different package name. This package would be imported as packages.
// This is how versions in pacakges like google.golang.org/api/slides/v1
// would be imported as package names instead of version tags.
package packages

import "fmt"

func Use() {
	fmt.Println("Hello world.")
}
