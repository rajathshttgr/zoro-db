package handlers

import (
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"zoro/api/dto"
	"zoro/api/services"
)

func UpsertPoint(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

	var req dto.UpsertPointsRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	if err := services.UpsertPoints(
		collectionName,
		req.Vectors,
		req.Ids,
		req.Payload,
	); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	// default config values
	status := "success"

	latency := float64(time.Since(start).Nanoseconds()) / 1e6


	resp := dto.CollectionResponseLayout{
	Result: dto.UpsertPointsResult{
		Status:         status,
		CollectionName: collectionName,
		Upserted:       1,
	},
	Time: latency,
	}

	c.JSON(http.StatusOK, resp)

}
