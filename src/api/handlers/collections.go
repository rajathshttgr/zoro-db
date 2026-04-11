package handlers

import (
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"zoro/dto"
	"zoro/services"
)

func CreateCollection(c *gin.Context) {
	start := time.Now()
	collectionName := c.Param("collection_name")

	var req dto.CreateCollectionRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": err.Error(),
		})
		return
	}

	if err := services.CreateCollection(
		collectionName,
		req.Vectors.Size,
		req.Vectors.Distance,
	); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	latency := float64(time.Since(start).Nanoseconds()) / 1e6

	resp := dto.CreateCollectionResult{
		Result:	   true,
		Status:    "ok",
		Time:      latency,
	}

	c.JSON(http.StatusCreated, resp)

}



func DeleteCollection(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

	if err := services.DeleteCollection(collectionName); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	latency := float64(time.Since(start).Nanoseconds()) / 1e6


	resp := dto.DeleteCollectionResult{
		Result:	   true,
		Status:    "ok",
		Time:      latency,
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

    collections_list := make([]dto.CollectionInfo, 0, len(collections))

    for _, col := range collections {
        collections_list = append(collections_list, dto.CollectionInfo{
            Name:     col.Name,
            Size:     col.Size,
            Distance: col.Distance,
			Status:   col.Status,
        })
    }

	result := dto.CollectionsResult{
		CollectionCount: len(collections),
		Collections: collections_list,
	}

    latency := float64(time.Since(start).Nanoseconds()) / 1e6

    resp := dto.ResponseLayout{
        Result: result,
		Status: "ok",
        Time:   latency,
    }

    c.JSON(http.StatusOK, resp)
}


func CheckCollectionExists(c *gin.Context){
	start := time.Now()

	collectionName := c.Param("collection_name")

	exists, err := services.CheckCollectionExists(collectionName)
	if err != nil {
        c.JSON(http.StatusBadRequest, gin.H{
            "error": err.Error(),
        })
        return
    }

    latency := float64(time.Since(start).Nanoseconds()) / 1e6

	result := dto.CollectionExists{
		Exists: exists,
	}

    resp := dto.ResponseLayout{
        Result: result,
		Status: "ok",
        Time:   latency,
    }

    c.JSON(http.StatusOK, resp)
}



func GetCollectionInfo(c *gin.Context) {
	start := time.Now()

	collectionName := c.Param("collection_name")

    collection, err := services.GetCollectionDetails(collectionName)
    if err != nil {
        c.JSON(http.StatusBadRequest, gin.H{
            "error": err.Error(),
        })
        return
    }

	latency := float64(time.Since(start).Nanoseconds()) / 1e6


	vector_config := dto.VectorConfigDetails{
		Size:        collection.Size,
		Distance:    collection.Distance,
	}

	config_details := dto.ConfigDetails{
		Name:       collection.Name,
		InternalId: "8fa3c1d2", // placeholder, can be generated or fetched from service layer
		Vectors:    vector_config,
	}

	result := dto.CollectionDetails{
		Status:       collection.Status,
		PointsCount:  0,
		SegmentCount: 6, 
		Config:       config_details,
	}

    resp := dto.ResponseLayout{
        Result: result,
		Status: "ok",
        Time:   latency,
    }

    c.JSON(http.StatusOK, resp)
}

