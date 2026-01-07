package handlers

import (
	"net/http"
	"time"
	"strconv"
	
	"github.com/gin-gonic/gin"
	"zoro/api/dto"
	"zoro/api/services"
)

func GetPointById(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")
	pointIdStr := c.Param("point_id")

	pointId, err := strconv.Atoi(pointIdStr)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "Invalid point ID",
		})
		return
	}

	point, err := services.GetPointById(collectionName, pointId)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	latency := float64(time.Since(start).Nanoseconds()) / 1e6

	resp := dto.CollectionResponseLayout{
		Result: dto.PointRetriveResult{
			Status:  point.Status,
			PointId: pointId,
			Payload: point.Payload, 
		},
		Time: latency,
	}

	c.JSON(http.StatusOK, resp)
}

func SearchPoints(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

	var req dto.SearchPointsRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	retrieval, err := services.SearchPoints(
		collectionName,
		req.Vectors,
		req.Limit,
	)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	result := make([]dto.PointSearchResult, 0, retrieval.Count)

	for _, p := range retrieval.Points {
		result = append(result, dto.PointSearchResult{
			PointId: p.PointId,
			Score:   p.Score,
			Payload: p.Payload,
		})
	}

	latency := float64(time.Since(start).Nanoseconds()) / 1e6

	resp := dto.CollectionResponseLayout{
		Result: result,
		Time:   latency,
	}

	c.JSON(http.StatusOK, resp)
}
