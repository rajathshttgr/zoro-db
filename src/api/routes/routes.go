package routes

import (
	"github.com/gin-gonic/gin"
	"zoro/handlers"
)

func RegisterRoutes(r *gin.Engine) {
	// System
	r.GET("/version", handlers.Version)
	r.GET("/health", handlers.Health)
	r.GET("/ping", handlers.Ping)

	// Collection
	r.POST("/collections/:collection_name", handlers.CreateCollection)  // Create a Collection
	r.DELETE("/collections/:collection_name",handlers.DeleteCollection) // Delete a Collection
	r.GET("/collections/:collection_name",handlers.GetCollectionInfo) // Get collection details
	r.GET("/collections/:collection_name/exists",handlers.CheckCollectionExists) // Check Collection Exists
	r.GET("/collections",handlers.GetCollections) // List all Collections
	
	// Points
	r.POST("/collections/:collection_name/points", handlers.UpsertPoint)
	r.DELETE("/collections/:collection_name/points", handlers.DeletePoints)
	r.GET("/collections/:collection_name/count", handlers.GetPointCount)

	// Search
	r.GET("/collections/:collection_name/points/:point_id", handlers.GetPointById)
	r.POST("/collections/:collection_name/points/scroll", handlers.GetScrollPoints)
	r.POST("/collections/:collection_name/points/search", handlers.SearchPoints)
}

