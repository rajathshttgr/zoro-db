package main

import (
    "log"
	"github.com/gin-gonic/gin"
	"zoro/api/api"
    "zoro/api/utils"
    "zoro/api/core"
)

func main() {

    utils.PrintBanner()

	if err := core.InitFromEnv(); err != nil {
		log.Fatal("failed to init core:", err)
	}
	
	defer core.Shutdown()
    
	r := gin.Default()

	r.GET("/", func(c *gin.Context) {
		c.String(200, "Welcome to Zoro-DB REST API!")
	})

	r.HEAD("/", func(c *gin.Context) {
        c.Status(200) 
    })

    api.RegisterRoutes(r)

    log.Println("Listening on :6464")
	r.Run(":6464") 
    
}