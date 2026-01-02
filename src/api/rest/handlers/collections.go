package handlers

import (
	"net/http"
	"time"
	"strconv"

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

	if err := services.DeleteCollection(collectionName); err != nil {
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
    start := time.Now()

    collections, err := services.ListCollections()
    if err != nil {
        c.JSON(http.StatusBadRequest, gin.H{
            "error": err.Error(),
        })
        return
    }

    result := make([]dto.CollectionInfoResult, 0, len(collections))

    for _, col := range collections {
        result = append(result, dto.CollectionInfoResult{
            CollectionName: col.Name,
            Dimension:      strconv.Itoa(col.Dimension),
            Distance:       col.Distance,
            Status:         col.Status,
        })
    }

    latency := float64(time.Since(start).Nanoseconds()) / 1e6

    resp := dto.CollectionResponseLayout{
        Result: result,
        Time:   latency,
    }

    c.JSON(http.StatusOK, resp)
}


func GetCollectionInfo(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

    collection, err := services.GetCollectionInfo(collectionName)
    if err != nil {
        c.JSON(http.StatusBadRequest, gin.H{
            "error": err.Error(),
        })
        return
    }

	latency := float64(time.Since(start).Nanoseconds()) / 1e6

	resp := dto.CollectionResponseLayout{
	Result: dto.CollectionInfoResult{
		CollectionName: collection.Name,
		Dimension:      strconv.Itoa(collection.Dimension),
		Distance:       collection.Distance,
		Status:         collection.Status,
	},
	Time: latency,
	}

    c.JSON(http.StatusOK, resp)
}

