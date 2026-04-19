package handlers

import (
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"zoro/dto"
	"zoro/services"
)

func UpsertPoints(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

	var req dto.UpsertPointsRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	operationId, err := services.UpsertPoints(
		collectionName,
		req.Points,
	)

	if err != nil {
		c.JSON(http.StatusNotFound, gin.H{
			"error": err.Error(),
		})
		return
}
	latency := time.Since(start).Seconds() 

	resp := dto.ResponseLayout{
		Result: dto.UpsertPointsResult{
			Status:       "acknowledged",
			Operation_Id:  operationId,
		},
		Status: "ok",
        Time:   latency,
	}

	c.JSON(http.StatusOK, resp)
}

func DeletePoints(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

	var req dto.DeletePointsRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	if err := services.DeletePoints(
		collectionName,
		req.Ids,
	); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	latency := time.Since(start).Seconds()

	resp := dto.CollectionResponseLayout{
		Result: dto.DeletePointsResult{
			Status:         "success",
			CollectionName: collectionName,
			Deleted:       len(req.Ids),
		},
		Time: latency,
	}

	c.JSON(http.StatusOK, resp)
}


func GetPointCount(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

	count, err := services.GetPointCount(collectionName)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	latency := time.Since(start).Seconds()
	// latency := float64(time.Since(start).Nanoseconds()) / 1e6

	resp := dto.CollectionResponseLayout{
		Result: dto.CollectionPointsInfoResult{
			CollectionName: collectionName,
			PointsCount:    count,
			Status:         "success",
		},
		Time: latency,
	}

	c.JSON(http.StatusOK, resp)
}