package main
 
import (
    "fmt"
    "log"
		"net/http"
		"sync/atomic"
		"sync"
		"github.com/aws/aws-sdk-go/aws"
    "github.com/aws/aws-sdk-go/aws/session"
		// "github.com/aws/aws-sdk-go/service/s3"
		"github.com/aws/aws-sdk-go/service/s3/s3manager"
		"os"
)

func hello(w http.ResponseWriter, r *http.Request) {
    if r.URL.Path != "/" {
        http.Error(w, "404 not found.", http.StatusNotFound)
        return
    }
 
    switch r.Method {
    case "POST":
        // Call ParseForm() to parse the raw query and update r.PostForm and r.Form.
        if err := r.ParseForm(); err != nil {
            fmt.Fprintf(w, "ParseForm() err: %v", err)
            return
        }
        filePath := r.FormValue("filename")
				bucket := r.FormValue("bucket")
				key := r.FormValue("key")
        // fmt.Fprintf(w, "Name = %s\n", name)
				// fmt.Fprintf(w, "Address = %s\n", address)
				

				urls := []string{
					"/home/ubuntu/hls-demo.js",
				// 	"/home/ubuntu/hls.js",
				// 	"/home/ubuntu/hls.light.js",
				// 	"/home/ubuntu/hls.min.js",
				// 	"/home/ubuntu/hls.light.min.js",
				}

				var wg sync.WaitGroup
			
				for _, u := range urls {
					// Increment the wait group counter
					wg.Add(1)
					go func(url string) {
						// Decrement the counter when the go routine completes
						defer wg.Done()
						// Call the function check
						checkUrl(filePath, bucket, key)
					}(u)
				}
				// Wait for all the checkWebsite calls to finish
				// wg.Wait()
				fmt.Fprintf(w, "filePath = %s\n", filePath)
				fmt.Fprintf(w, "Address = %s\n", bucket)
				fmt.Fprintf(w, "Key = %s\n", key)
    default:
        fmt.Fprintf(w, "Sorry, only GET and POST methods are supported.")
    }
}
 
//checks and prints a message if a website is up or down
func checkUrl(fileName string, bucket string, key string) {
	// _, err := http.Get(url)
	// if err != nil {
	// 	fmt.Println(url, "is down !!!")
	// 	return
	// }
	// fmt.Println(url, "is up and running.")

	sess, err := session.NewSession(&aws.Config{
		Region: aws.String("ap-south-1")},
	);
	// svc := s3.New(sess);
	file, err := os.Open(fileName)
	if err != nil {
		log.Println("ERROR:", err)
		return
	}

	fileInfo, err := file.Stat()
	if err != nil {
		log.Println("ERROR:", err)
		return
	}

	reader := &CustomReader{
		fp:   file,
		size: fileInfo.Size(),
	}

	uploader := s3manager.NewUploader(sess, func(u *s3manager.Uploader) {
		u.PartSize = 5 * 1024 * 1024
		u.LeavePartsOnError = true
	})

	output, err := uploader.Upload(&s3manager.UploadInput{
		Bucket: aws.String(bucket),
		Key:    aws.String(key),
		Body:   reader,
	})

	if err != nil {
		log.Println("ERROR:", err)
		return
	}

	log.Println(output.Location)
}

func exitErrorf(msg string, args ...interface{}) {
	fmt.Fprintf(os.Stderr, msg+"\n", args...)
	os.Exit(1)
}

type CustomReader struct {
	fp   *os.File
	size int64
	read int64
}

func (r *CustomReader) Read(p []byte) (int, error) {
	return r.fp.Read(p)
}

func (r *CustomReader) ReadAt(p []byte, off int64) (int, error) {
	n, err := r.fp.ReadAt(p, off)
	if err != nil {
		return n, err
	}

	// Got the length have read( or means has uploaded), and you can construct your message
	atomic.AddInt64(&r.read, int64(n))

	// I have no idea why the read length need to be div 2,
	// maybe the request read once when Sign and actually send call ReadAt again
	// It works for me
	// log.Printf("total read:%d    progress:%d%%\n", r.read/2, int(float32(r.read*100/2)/float32(r.size)))

	return n, err
}

func (r *CustomReader) Seek(offset int64, whence int) (int64, error) {
	return r.fp.Seek(offset, whence)
}

func main() {
    http.HandleFunc("/", hello)
 
    fmt.Printf("Starting server for testing HTTP POST...\n")
    if err := http.ListenAndServe(":8080", nil); err != nil {
        log.Fatal(err)
    }
}