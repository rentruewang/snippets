package main

import (
	"fmt"
	"log"
	"net/http"
	"strings"

	"github.com/gin-gonic/gin"
	"github.com/valyala/fasthttp"
)

// These should be provided as environment variables
// But are hard coded for convenience
const APIKEY = "AIzaSyCMFQ9uzH69tuKn01AlUGlx53qlQ8OauyM"
const SECRETURL = "https://asia-northeast2-driven-cabinet.cloudfunctions.net/rest"

func makeReq(method, data string) string {
	req := fasthttp.AcquireRequest()
	req.Header.SetMethod(method)
	req.SetRequestURI(SECRETURL)
	req.SetBodyString(data)
	defer fasthttp.ReleaseRequest(req)

	res := fasthttp.AcquireResponse()
	defer fasthttp.ReleaseResponse(res)

	if err := fasthttp.Do(req, res); err != nil {
		log.Fatalln(err)
	}
	if stat := res.StatusCode(); stat != fasthttp.StatusOK {
		log.Fatalln("Error code: " + fmt.Sprint(stat))
	}

	return string(res.Body())
}

func makeQuery(input string) string {
	return "&q=" + strings.Join(strings.Fields(input), "+")
}

func main() {
	r := gin.Default()

	src := fmt.Sprintf("https://www.google.com/maps/embed/v1/place?key=%s", APIKEY)

	query := "&q=Taipei"

	r.LoadHTMLFiles("./templates/debug.tmpl")

	// gin methods here
	// GET for the main page
	r.GET("/", func(ctx *gin.Context) {
		ctx.HTML(int(http.StatusOK), "debug.tmpl", gin.H{"SOURCE": src + query})
	})

	// Fetch a new place from GCF
	r.GET("/newplace", func(ctx *gin.Context) {
		ans := makeReq("GET", "")
		query = makeQuery(ans)
		log.Println(ans, query)
		ctx.Redirect(fasthttp.StatusPermanentRedirect, "/")
		ctx.Abort()
	})

	// Save place to GCF
	r.GET("/gotohere", func(ctx *gin.Context) {
		loc := ctx.Query("loc")
		makeReq("POST", loc)
		query = makeQuery(loc)

		ctx.Redirect(fasthttp.StatusPermanentRedirect, "/")
		ctx.Abort()
	})

	// Delete place from GCF
	r.GET("/deletethis", func(ctx *gin.Context) {
		loc := strings.ReplaceAll(query[3:], "+", " ")
		ans := makeReq("DELETE", loc)
		query = makeQuery(ans)

		ctx.Redirect(fasthttp.StatusPermanentRedirect, "/")
		ctx.Abort()
	})

	// For debug use
	r.GET("/debug", func(ctx *gin.Context) {
		data := makeReq("GET", "")
		ctx.JSON(fasthttp.StatusOK, data)
	})
	r.Run(":8080")
}
