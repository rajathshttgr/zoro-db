package handlers

import (
	"encoding/json"
	"net/http"
	"strconv"
	"time"

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
			"error": "point_id must be an integer",
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

	var payload []map[string]any
	if err := json.Unmarshal(point.Payload, &payload); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{
			"error": "invalid payload format",
		})
		return
	}

	latency := float64(time.Since(start).Nanoseconds()) / 1e6

	resp := dto.CollectionResponseLayout{
		Result: dto.PointRetriveResult{
			Status:  point.Status,
			PointId: pointId,
			Payload: payload,
		},
		Time: latency,
	}

	c.JSON(http.StatusOK, resp)
}
