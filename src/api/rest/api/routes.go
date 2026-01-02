package api

import (
	"github.com/gin-gonic/gin"
	"zoro/api/handlers"
)

func RegisterRoutes(r *gin.Engine) {
	//System
	r.GET("/health", handlers.Health)
	r.GET("/version", handlers.Version)
	r.GET("/ping", handlers.Ping)

	//Collection
	r.POST("/collections",handlers.CreateCollection)
	r.DELETE("/collections/:collection_name",handlers.DeleteCollection)
	r.GET("/collections",handlers.GetCollections)
	r.GET("/collections/:collection_name",handlers.GetCollectionInfo)

	//Points
	r.POST("/collections/:collection_name/points", handlers.UpsertPoint)
	r.DELETE("/collections/:collection_name/points", handlers.DeletePoints)
	r.GET("/collections/:collection_name/count", handlers.GetPointCount)
	// r.POST("/collections/:collection_name/points/search")
}

