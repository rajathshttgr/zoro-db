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

	latency := float64(time.Since(start).Nanoseconds()) / 1e6

	// default config values
	sharding := 1
	status := "active"

	resp := dto.CollectionResponseLayout{
	Result: dto.CreateCollectionResult{
		Status:         status,
		CollectionName: req.CollectionName,
		Dimension:      req.Dimension,
		Distance:       req.Distance,
		Sharding:       sharding,
	},
	Time: latency,
	}

	c.JSON(http.StatusOK, resp)

}



func DeleteCollection(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

	if err := services.DeleteCollection( collectionName); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	latency := float64(time.Since(start).Nanoseconds()) / 1e6

	// default status
	status := "deleted"

	resp := dto.CollectionResponseLayout{
	Result: dto.DeleteCollectionResult{
		Status:         status,
		CollectionName: collectionName,
	},
	Time: latency,
	}

	c.JSON(http.StatusOK, resp)
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

