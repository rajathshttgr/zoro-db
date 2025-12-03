package handlers

import (
	"github.com/gin-gonic/gin"
	"net/http"
)

func Search(c *gin.Context){
	c.JSON(http.StatusOK,gin.H{
		"hits":[]gin.H{
			{"id":"vec_1","score":0.12},
			{"id":"vec_2","score":0.34},
		},
	})
}