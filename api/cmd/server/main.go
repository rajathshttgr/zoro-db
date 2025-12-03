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

	router.POST("/collections/create", handlers.CreateCollectionHandler)
	router.GET("/collections", handlers.ListCollections)

	router.POST("/vectors/add", handlers.AddVectors)

	router.POST("/search", handlers.Search)

	router.Run(":8080")
}
