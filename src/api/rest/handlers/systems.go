package handlers

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func Version(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{
		"version": "1.0.0",
	})
}

func Ping(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{
		"message": "pong",
	})
}

func Health(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{
		"message": "green",
	})
}
