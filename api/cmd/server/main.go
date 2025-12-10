package main

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"zoro-api/internal/handlers"
)

func main() {
	router := gin.Default()

	router.GET("/health", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{"status": "ok"})
	})

	router.POST("/init", handlers.InitEngineHandler)

	router.POST("/search", handlers.Search)

	router.Run(":8080")
}
