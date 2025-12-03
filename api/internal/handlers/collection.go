package handlers

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"zoro/api/internal/engine"
)

// request body model
type CreateCollectionRequest struct {
	Name       string `json:"name" binding:"required"`
	Dimension  int    `json:"dimension" binding:"required"`
}

func CreateCollectionHandler(c *gin.Context) {
	var req CreateCollectionRequest

	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"ok":      false,
			"error":   "invalid body: " + err.Error(),
		})
		return
	}

	err := engine.CreateCollection(req.Name, req.Dimension)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{
			"ok":     false,
			"error":  err.Error(),
		})
		return
	}

	c.JSON(http.StatusOK, gin.H{
		"ok":        true,
		"message":   "collection created",
		"collection": req.Name,
	})
}







