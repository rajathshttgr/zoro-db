package handlers

import (
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"zoro/api/dto"
	"zoro/api/services"
)

func CreateCollection(c *gin.Context) {
	start := time.Now()

	var req dto.CreateCollectionRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	if err := services.CreateCollection(
		req.CollectionName,
		req.Dimension,
		req.Distance,
	); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	latency := time.Since(start).Milliseconds()

	// data mocked for now
	sharding := 1
	status := "ACTIVE"

	c.JSON(http.StatusOK, gin.H{
		"collection_name": req.CollectionName,
		"dimension":       req.Dimension,
		"distance":        req.Distance,
		"sharding":        sharding,
		"status":          status,
		"latency_ms":      latency,
	})
}

func DeleteCollection(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{
		"message": "collection created successfully",
	})
}


func GetCollections(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{
		"message": "collection created successfully",
	})
}

func GetCollectionInfo(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{
		"message": "collection created successfully",
	})
}

