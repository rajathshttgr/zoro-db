package main

import (
	"context"
	"log"
	"net/http"
	"os"
	"os/signal"
	"syscall"
	"time"

	"github.com/gin-gonic/gin"
	"zoro/api/api"
	"zoro/api/core"
	"zoro/api/utils"
)

func main() {
	utils.PrintBanner()

	if err := core.InitFromEnv(); err != nil {
		log.Fatal("failed to init core:", err)
	}

	r := gin.Default()

	r.GET("/", func(c *gin.Context) {
		c.String(200, "Welcome to Zoro-DB REST API!")
	})

	api.RegisterRoutes(r)

	srv := &http.Server{
		Addr:    ":6464",
		Handler: r,
	}

	go func() {
		log.Println("Listening on :6464")
		if err := srv.ListenAndServe(); err != nil && err != http.ErrServerClosed {
			log.Fatalf("listen error: %v", err)
		}
	}()

	quit := make(chan os.Signal, 1)
	signal.Notify(quit, syscall.SIGINT, syscall.SIGTERM)
	<-quit

	log.Println("Shutting down server...")

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	if err := srv.Shutdown(ctx); err != nil {
		log.Printf("Server forced to shutdown: %v", err)
	}

	core.Shutdown()
	log.Println("Server exited cleanly")
}
