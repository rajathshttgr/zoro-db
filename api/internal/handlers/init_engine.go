package handlers

import (
	"github.com/gin-gonic/gin"
	"net/http"
	"zoro-api/internal/engine"
)

func InitEngineHandler(c *gin.Context){
	err := engine.InitEngine()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{
			"ok":     false,
			"error":  err.Error(),
		})
		return
	}

	c.JSON(http.StatusOK, gin.H{
		"ok":        true,
		"message":   "Engine initialized",
	})
}